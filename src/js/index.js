// Використовуємо fetch для отримання вмісту файлу та відображення його
function fetchAndDisplayContent(url, codeId, textId) {
    fetch(url)
        .then(response => response.text())
        .then(data => {
            document.getElementById(codeId).textContent = data;
            Prism.highlightAll();
        });
    fetch(url)
        .then(response => response.text())
        .then(data => {
            var preElement = document.createElement('pre');
            preElement.textContent = data;
            var textContainer = document.getElementById(textId);
            textContainer.innerHTML = '';
            textContainer.appendChild(preElement);
        });
}

// JavaScript-функція для прокручування до певного пункту
function scrollToSection(button) {
    var targetId = button.getAttribute('data-target');
    var element = document.getElementById(targetId);
    element.scrollIntoView({ behavior: 'smooth' });
}



// Функція для завантаження вмісту з іншого HTML файлу
function loadContent(url, targetId) {
    var xhr = new XMLHttpRequest();
    xhr.open('GET', url, true);
    xhr.onreadystatechange = function () {
        if (xhr.readyState === 4 && xhr.status === 200) {
            document.getElementById(targetId).innerHTML = xhr.responseText;
        }
    };
    xhr.send();
}
