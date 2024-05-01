const sidenavLinks = document.querySelectorAll(".sidenav-links");
const sidenavMobile = document.querySelector("#sidenav-mobile");
const hamburgerBtn = document.querySelector("#topbar .c-hamburger-btn");
const activeNavItemClassName = "c-nav-item-active";
const mediumSizeDeviceScreenWidth = 786;

const setActiveNavItem = () => {
    let url = window.location.href;
    sidenavLinks.forEach((sidenav) => {
        sidenav.querySelectorAll("li").forEach((li) => {
            let link = li.querySelector("a").href;

            if (link === url && !li.classList.contains(activeNavItemClassName)) {
                li.classList.add(activeNavItemClassName);
            } else {
                li.classList.remove(activeNavItemClassName);
            }
        })
    })
}

window.addEventListener("click", (element) => {
    if (window.innerWidth > mediumSizeDeviceScreenWidth) {
        return;
    }

    if (
        sidenavMobile !== null
        && sidenavMobile.classList.contains("c-sidenav-mobile-open")
        && !hamburgerBtn.contains(element.target)
        && !sidenavMobile.contains(element.target)
    ) {
        console.log("clickoutside!");
        sidenavMobile.classList.toggle("c-sidenav-mobile-open");
    }
});

setActiveNavItem();
