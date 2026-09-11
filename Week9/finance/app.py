import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    """Show portfolio of stocks"""

    if request.method == "POST":
        cash_amount = request.form.get("cash_amount")

        # Validate input
        if not cash_amount:
            return apology("Enter the amount")

        try:
            cash_amount = int(cash_amount)
            if cash_amount <= 0:
                return apology("amount must be positive")
        except (ValueError, SyntaxError):
            return apology("Provide whole number")

        # Add cash to balance
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", cash_amount, session["user_id"])

        flash("Cash added!")
        return redirect("/")


    STOCKS = db.execute(
        "SELECT stock_name,stock_shares FROM portfolios WHERE user_id = ? ORDER BY stock_shares DESC", session["user_id"])
    # Retrieve current price of stocks
    stocks = []
    total_stocks_value = 0

    for STOCK in STOCKS:
        stock = lookup(STOCK["stock_name"])
        stocks.append({**stock, "shares": STOCK["stock_shares"]})
        total_stocks_value += stock["price"] * STOCK["stock_shares"]
    # Get users cash
    cash = db.execute("SELECT cash FROM users WHERE id = ? ", session["user_id"])[0]["cash"]

    return render_template("index.html", stocks=stocks, cash=cash, total_stocks=total_stocks_value or 0)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        stock = lookup(symbol)

        # Validate Input
        if not stock or not shares:
            return apology("Please fill all the fields and provide correct symbol")

        try:
            shares = int(shares)
            if shares < 1 or not shares.is_integer():
                return apology("Shares must be postive whole number")
        except (ValueError, TypeError):
            return apology("Shares must be number")

        # Validate if user has enough money to buy stocks
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        money_spent = stock["price"] * shares

        if money_spent > user_cash:
            return apology("You do not have sufficient balance")

        # Make a purchase
        user_cash -= money_spent
        db.execute("UPDATE users SET cash = ? WHERE id = ?", user_cash, session["user_id"])
        db.execute("INSERT INTO transactions(user_id,stock_name,stock_price,stock_shares) VALUES(?,?,?,?)",
                   session["user_id"], stock["symbol"], stock["price"], shares)

        db.execute("INSERT INTO portfolios(user_id,stock_name,stock_shares) VALUES(?,?,?) ON CONFLICT(user_id,stock_name) DO UPDATE SET stock_shares = stock_shares + excluded.stock_shares",
                   session["user_id"], stock["symbol"], shares)

        flash("Bought!")
        return redirect('/')

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT * FROM transactions WHERE user_id = ?", session["user_id"])
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        flash("Logged in!")
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        #  Get stock information
        stock = lookup(request.form.get("symbol"))
        if stock is None:
            return apology("Stock not found")
        return render_template("quoted.html", stock=stock)

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Validate input
        if not username or not password or not confirmation:
            return apology("Fill all the fields")
        if not password == confirmation:
            return apology("Passwords do not match")

        # Register the user if username is not already exists
        try:
            id = db.execute("INSERT INTO users(username,hash) VALUES(?,?)",
                            username, generate_password_hash(password))
            session["user_id"] = id

            flash("Registered!")
            return redirect('/')
        except ValueError:
            return apology("Username already exists")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Validate input
        if not symbol or not shares:
            return apology("Fill all the fields")

        try:
            shares = int(shares)
            if shares < 1:
                return apology("Provide reasonable number")
        except (ValueError, SyntaxError):
            return apology("shares must be whole number")

        user_stocks = db.execute("SELECT * FROM portfolios WHERE user_id = ?", session["user_id"])
        # Check if user actually has stock and enough share
        for stock in user_stocks:
            if stock["stock_name"] == symbol and stock["stock_shares"] >= shares:
                break
        else:
            return apology("Not enough shares or invalid stock")

        # Sell the stock and update database
        stock_price = lookup(symbol)["price"]
        earning = stock_price * shares
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash + earning, session["user_id"])

        # Update transactions and portfolios
        db.execute("INSERT INTO transactions(user_id,stock_name,stock_price,stock_shares) VALUES(?,?,?,?)",
                   session["user_id"], symbol.upper(), stock_price, -shares)
        db.execute("UPDATE portfolios SET stock_shares = stock_shares - ? WHERE user_id = ? AND stock_name = ?",
                   shares, session["user_id"], symbol.upper())
        db.execute("DELETE FROM portfolios WHERE stock_shares <= 0")

        flash("Sold!")
        return redirect("/")

    # Retrive what stocks user have
    symbols = db.execute(
        "SELECT DISTINCT stock_name FROM portfolios WHERE user_id = ?", session["user_id"])
    return render_template("sell.html", symbols=symbols)

if __name__ == "__main__":
    app.run(debug=True)