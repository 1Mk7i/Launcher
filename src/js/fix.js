// скрипт для видалення даних сайту щоб він не зберігався в пам'яті браузера
// викликається при закритті вікна
// видаляє всі дані з localStorage
window.onbeforeunload = function () {
    localStorage.clear();
};