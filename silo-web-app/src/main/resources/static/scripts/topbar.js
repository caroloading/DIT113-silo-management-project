const hamburgerBtn = document.querySelector("#topbar .c-hamburger-btn");
const sidenavMobile = document.getElementById("sidenav-mobile");

hamburgerBtn.addEventListener("click", () => {
    sidenavMobile.classList.toggle("c-sidenav-mobile-open");
});