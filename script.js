const repoBtn = document.getElementById("repo");
const personBtn = document.getElementById("person");
const welcomeTitle = document.querySelector("#welcome h1");

const textoParaDigitar = "Welcome to the Whispers of Condemnation main page!";
welcomeTitle.innerText = ""; 

let charIndex = 0;
function typeEffect() {
    if (charIndex < textoParaDigitar.length) {
        let char = textoParaDigitar.charAt(charIndex);
        welcomeTitle.innerHTML += (char === " ") ? "&nbsp;" : char;
        charIndex++;
        setTimeout(typeEffect, 60);
    }
}

const handleButtonClick = (url, btn) => {
    btn.classList.add("btn-active"); 
    setTimeout(() => {
        btn.classList.remove("btn-active");
        window.open(url, '_blank');
    }, 150); 
};

repoBtn.addEventListener("click", () => {
    handleButtonClick('https://github.com/JustAcoder617/Whispers-of-Condemnation', repoBtn);
});

personBtn.addEventListener("click", () => {
    handleButtonClick('https://github.com/JustAcoder617', personBtn);
});

window.onload = typeEffect;