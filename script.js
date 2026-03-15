const repoBtn = document.getElementById("repo");
const personBtn = document.getElementById("person");
const welcomeTitle = document.querySelector("#welcome h1");

// Texto que será digitado
const textoParaDigitar = "Welcome to the Whispers of Condemnation main page!";

// Limpa o título e prepara o cursor
welcomeTitle.innerText = ""; 

let charIndex = 0;

function typeEffect() {
    if (charIndex < textoParaDigitar.length) {
        let char = textoParaDigitar.charAt(charIndex);
        
        // Mantém o cursor sempre no final durante a digitação
        welcomeTitle.innerHTML = textoParaDigitar.substring(0, charIndex + 1) + '<span class="cursor">|</span>';
        
        charIndex++;
        setTimeout(typeEffect, 60);
    } else {
        // Quando termina, o cursor continua piscando no final
        welcomeTitle.innerHTML = textoParaDigitar + '<span class="cursor">|</span>';
    }
}

// Lógica de animação e redirecionamento dos botões
const handleButtonClick = (url, btn) => {
    btn.classList.add("btn-active"); 
    setTimeout(() => {
        btn.classList.remove("btn-active");
        window.open(url, '_blank');
    }, 150); 
};

// Eventos dos botões
repoBtn.addEventListener("click", () => {
    handleButtonClick('https://github.com/JustAcoder617/Whispers-of-Condemnation', repoBtn);
});

personBtn.addEventListener("click", () => {
    handleButtonClick('https://github.com/JustAcoder617', personBtn);
});

// Inicia o efeito quando a página carregar
window.onload = typeEffect;