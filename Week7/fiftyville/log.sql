-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT * FROM crime_scene_reports WHERE  street = 'Humphrey Street';

SELECT * FROM bakery_security_logs WHERE year=2025 AND month = 7 AND day = 28 AND hour = 10;
SELECT * FROM interviews WHERE year=2025 AND month = 7 AND day = 28;
SELECT * FROM atm_transactions WHERE year=2025 AND month = 7 AND day = 28 AND atm_location LIKE '%Legget%';

SELECT * FROM phone_calls WHERE year=2025 AND month = 7 AND day = 28 AND duration <= 60;

SELECT * FROM people WHERE license_plate IN (
    SELECT license_plate FROM bakery_security_logs WHERE year=2025 AND month = 7 AND day = 28 AND hour = 10);

SELECT * FROM phone_calls WHERE year=2025 AND month = 7 AND day = 28 AND duration <= 60 AND caller IN (SELECT phone_number FROM people WHERE
license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year=2025 AND month = 7 AND day = 28 AND hour = 10));



-- flight ID
SELECT id FROM flights WHERE year = 2025 AND day = 29 AND month = 7 ORDER BY hour DESC LIMIT 1;

-- Found the city they escaped to
SELECT city FROM airports WHERE id = (SELECT destination_airport_id  FROM flights WHERE year = 2025 AND day = 29 AND month = 7 ORDER BY hour ASC LIMIT 1
);


-- passports of flight attentands
SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE year = 2025 AND day = 29 AND month = 7 ORDER BY hour ASC LIMIT 1);

-- passport numbers of suspects
SELECT passport_number FROM people WHERE phone_number IN (
        SELECT caller FROM phone_calls WHERE year=2025 AND month = 7 AND day = 28 AND duration <= 60 AND caller IN (
            SELECT phone_number FROM people WHERE license_plate IN (
                    SELECT license_plate FROM bakery_security_logs WHERE year=2025 AND month = 7 AND day = 28 AND hour = 10)));





-- Four suspect in plane
SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE year = 2025 AND day = 29 AND month = 7 ORDER BY hour ASC LIMIT 1) AND passport_number IN (SELECT passport_number FROM people WHERE phone_number IN (
     SELECT caller FROM phone_calls WHERE year=2025 AND month = 7 AND day = 28 AND duration <= 60 AND caller IN (
                SELECT phone_number FROM people WHERE license_plate IN (
                        SELECT license_plate FROM bakery_security_logs WHERE year=2025 AND month = 7 AND day = 28 AND hour = 10))));

-- Two suspects remaining
SELECT * FROM atm_transactions WHERE account_number IN (SELECT account_number FROM bank_accounts WHERE person_id IN (SELECT id FROM people WHERE passport_number IN(SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE year = 2025 AND day = 29 AND month = 7 ORDER BY hour ASC LIMIT 1) AND passport_number IN (SELECT passport_number FROM people WHERE phone_number IN (
     SELECT caller FROM phone_calls WHERE year=2025 AND month = 7 AND day = 28 AND duration <= 60 AND caller IN (
                SELECT phone_number FROM people WHERE license_plate IN (
                        SELECT license_plate FROM bakery_security_logs WHERE year=2025 AND month = 7 AND day = 28 AND hour = 10)))))));

-- Found thief
SELECT account_number FROM atm_transactions WHERE account_number IN (SELECT account_number FROM bank_accounts WHERE person_id IN (SELECT id FROM people WHERE passport_number IN(SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE year = 2025 AND day = 29 AND month = 7 ORDER BY hour ASC LIMIT 1) AND passport_number IN (SELECT passport_number FROM people WHERE phone_number IN (
     SELECT caller FROM phone_calls WHERE year=2025 AND month = 7 AND day = 28 AND duration <= 60 AND caller IN (
                SELECT phone_number FROM people WHERE license_plate IN (
                        SELECT license_plate FROM bakery_security_logs WHERE year=2025 AND month = 7 AND day = 28 AND hour = 10 AND minute < 30)))))));

-- thief id
SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE account_number IN (SELECT account_number FROM bank_accounts WHERE person_id IN (SELECT id FROM people WHERE passport_number IN(SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE year = 2025 AND day = 29 AND month = 7 ORDER BY hour ASC LIMIT 1) AND passport_number IN (SELECT passport_number FROM people WHERE phone_number IN (
     SELECT caller FROM phone_calls WHERE year=2025 AND month = 7 AND day = 28 AND duration <= 60 AND caller IN (
                SELECT phone_number FROM people WHERE license_plate IN (
                        SELECT license_plate FROM bakery_security_logs WHERE year=2025 AND month = 7 AND day = 28 AND hour = 10 AND minute < 30))))))));


-- thief name
SELECT name FROM people WHERE id = (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE account_number IN (SELECT account_number FROM bank_accounts WHERE person_id IN (SELECT id FROM people WHERE passport_number IN(SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE year = 2025 AND day = 29 AND month = 7 ORDER BY hour ASC LIMIT 1) AND passport_number IN (SELECT passport_number FROM people WHERE phone_number IN (
     SELECT caller FROM phone_calls WHERE year=2025 AND month = 7 AND day = 28 AND duration <= 60 AND caller IN (
                SELECT phone_number FROM people WHERE license_plate IN (
                        SELECT license_plate FROM bakery_security_logs WHERE year=2025 AND month = 7 AND day = 28 AND hour = 10 AND minute < 30)))))))));

-- thief phone number
SELECT phone_number FROM people WHERE id = (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE account_number IN (SELECT account_number FROM bank_accounts WHERE person_id IN (SELECT id FROM people WHERE passport_number IN(SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE year = 2025 AND day = 29 AND month = 7 ORDER BY hour ASC LIMIT 1) AND passport_number IN (SELECT passport_number FROM people WHERE phone_number IN (
     SELECT caller FROM phone_calls WHERE year=2025 AND month = 7 AND day = 28 AND duration <= 60 AND caller IN (
                SELECT phone_number FROM people WHERE license_plate IN (
                        SELECT license_plate FROM bakery_security_logs WHERE year=2025 AND month = 7 AND day = 28 AND hour = 10 AND minute < 30)))))))));


-- accomplice phone number
SELECT receiver FROM phone_calls WHERE year=2025 AND month = 7 AND day = 28 AND duration <= 60 AND caller = (SELECT phone_number FROM people WHERE id = (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE account_number IN (SELECT account_number FROM bank_accounts WHERE person_id IN (SELECT id FROM people WHERE passport_number IN(SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE year = 2025 AND day = 29 AND month = 7 ORDER BY hour ASC LIMIT 1) AND passport_number IN (SELECT passport_number FROM people WHERE phone_number IN (
     SELECT caller FROM phone_calls WHERE year=2025 AND month = 7 AND day = 28 AND duration <= 60 AND caller IN (
                SELECT phone_number FROM people WHERE license_plate IN (
                        SELECT license_plate FROM bakery_security_logs WHERE year=2025 AND month = 7 AND day = 28 AND hour = 10 AND minute < 30))))))))));
-- accomplice name
SELECT name FROM people WHERE phone_number = (
    SELECT receiver FROM phone_calls WHERE year=2025 AND month = 7 AND day = 28 AND duration <= 60 AND caller = (
        SELECT phone_number FROM people WHERE id = (
            SELECT person_id FROM bank_accounts WHERE account_number IN (
                SELECT account_number FROM atm_transactions WHERE account_number IN (
                    SELECT account_number FROM bank_accounts WHERE person_id IN (
                        SELECT id FROM people WHERE passport_number IN(
                            SELECT passport_number FROM passengers WHERE flight_id = (
                                SELECT id FROM flights WHERE year = 2025 AND day = 29 AND month = 7 ORDER BY hour ASC LIMIT 1) AND passport_number IN (
                                    SELECT passport_number FROM people WHERE phone_number IN (
                                        SELECT caller FROM phone_calls WHERE year=2025 AND month = 7 AND day = 28 AND duration <= 60 AND caller IN (
                                             SELECT phone_number FROM people WHERE license_plate IN (
                                                 SELECT license_plate FROM bakery_security_logs WHERE year=2025 AND month = 7 AND day = 28 AND hour = 10 AND minute < 30)))))))))));
