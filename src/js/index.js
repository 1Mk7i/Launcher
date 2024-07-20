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
    document.querySelectorAll('[data-code]').forEach(function(element) {
        const filePath = element.getAttribute('data-code');
        const PathFunction = element.getAttribute('data-function');
        // fetchAndDisplayContent(filePath, element.id);
        // перевіряємо, яка функція викликається
        if (PathFunction === 'loadContent') {
            loadContent(filePath, element.id);
        } else if (PathFunction === 'loadContentW') {
            loadContentW(filePath, element.id);
        } else if (PathFunction === 'fetchAndDisplayContent'){
            fetchAndDisplayContent(filePath, element.id);
        }
    });
    
    // створюємо кнопку для кожного елемента з атрибутоми linc-data та name-data (кнопки)
    var previews = document.querySelectorAll('.preview[link-data][name-data]');
    previews.forEach(function(preview) {
        var link = preview.getAttribute('link-data');
        var text = preview.getAttribute('name-data');
        var buttonHTML = '<div class="Button"><a class="btn btn-primary whiteb" href="' + link + '">' + text + '</a></div>';
        preview.innerHTML = buttonHTML;
    });
    // створюємо кнопку для кожного елемента з атрибутоми linc-data, name-data та image-data (кнопки з картинкою)
    var previews = document.querySelectorAll('.preview[link-data][name-data][image-data]');
    previews.forEach(function(preview) {
        var link = preview.getAttribute('link-data');
        var text = preview.getAttribute('name-data');
        var image = preview.getAttribute('image-data');
        var buttonHTML = '<img class="previewImg" src="'+ image +'" alt="preview"><div class="Button"><a class="btn btn-primary whiteb" href="'+ link +'">'+ text +'</a></div>';
        preview.innerHTML = buttonHTML;
    });
});

