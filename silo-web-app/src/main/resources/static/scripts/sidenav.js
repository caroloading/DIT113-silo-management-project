const sidenavLinks = document.querySelectorAll(".sidenav-links");
const activeNavItemClassName = "c-nav-item-active";

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

setActiveNavItem();
