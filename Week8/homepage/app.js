const daysEl = document.getElementById('days');
const hoursEl = document.getElementById('hours');
const minutesEl = document.getElementById('minutes');
const secondsEl = document.getElementById('seconds');

const dropdownBtn = document.querySelector('.menu svg');
const dropdownList = document.querySelector('.nav');

// Countdown

const RELEASE_DATE_MS = new Date("2026-11-19T00:00:00Z").getTime();

window.setInterval(() => {
    let differenceMS = RELEASE_DATE_MS - Date.now()
    let days = Math.trunc(differenceMS / 1000 / 86400);
    let hours = Math.trunc((differenceMS / 1000 / 3600) % 24);
    let minutes = Math.trunc((differenceMS / 1000 / 60) % 60);
    let seconds = Math.trunc((differenceMS / 1000)  % 60);

    daysEl.textContent = String(days).padStart(2,'0');
    hoursEl.textContent = String(hours).padStart(2,'0');
    minutesEl.textContent = String(minutes).padStart(2,'0');
    secondsEl.textContent = String(seconds).padStart(2,'0');
},1000)

// Drowdown menu
dropdownBtn.addEventListener('click', () => {
    dropdownList.classList.toggle('dropdown');
    dropdownBtn.classList.toggle('fixed');
})
