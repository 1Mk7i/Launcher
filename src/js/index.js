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
fetchAndDisplayContent('OOP-res/tasks/task1.cpp', 'Prak1OOPnum1');
fetchAndDisplayContent('OOP-res/tasks/task2.cpp', 'Prak1OOPnum2');
fetchAndDisplayContent('OOP-res/tasks/lab1.cpp', 'Lab1OOP');
fetchAndDisplayContent('OOP-res/tasks/Prak2OOPMain.cpp','Prak2OOPnum1')
fetchAndDisplayContent('OOP-res/tasks/Prak2OOPS1.cpp','Prak2OOPnum2')

// JavaScript-функція для прокручування до певного пункту
function scrollToSection(button) {
    var targetId = button.getAttribute('data-target');
    var element = document.getElementById(targetId);
    element.scrollIntoView({ behavior: 'smooth' });
}