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

// display change
function loadContentW(url, target) {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById(target).innerHTML = this.responseText;
            document.getElementById(target).style.display = "block";
        }
    };
    xhttp.open("GET", url, true);
    xhttp.send();
}

// викликаємо функцію для кожного елемента з атрибутом data-code
document.addEventListener('DOMContentLoaded', function() {
    const elements = document.querySelectorAll('[load-link]');

    elements.forEach(element => {
        const contentPath = element.getAttribute('load-link');

        element.addEventListener('click', function(event) {
            event.preventDefault();
            loadContent(contentPath, 'content2');
        });
    });
});

// Функція для завантаження вмісту за замовчуванням
function loadDefaultContent() {
    loadContent('/Launcher/src/pages/res/default.html', 'content2');
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

    setTimeout(function() {
        document.querySelectorAll('[data-code]').forEach(function(element) {
            const filePath = element.getAttribute('data-code');
            const PathFunction = element.getAttribute('data-function');
            if (PathFunction === 'loadContent') {
                loadContent(filePath, element.id);
            } else if (PathFunction === 'loadContentW') {
                loadContentW(filePath, element.id);
            } else if (PathFunction === 'fetchAndDisplayContent') {
                fetchAndDisplayContent(filePath, element.id);
            }
        });
    }, 2000); // 1000 мс = 1 секунда
}
// Завантаження вмісту за замовчуванням при завантаженні сторінки
window.onload = loadDefaultContent;
