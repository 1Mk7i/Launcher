const readlineSync = require('readline-sync');

// Структура Note
class Note {
    constructor(name, phone, bday) {
        this.name = name;
        this.phone = phone;
        this.bday = bday; // bday is an array [day, month, year]
    }
}

// Функція information
function information() {
    const N = 10;
    const BLOCKNOTE = [];

    // Вводимо дані про людей
    for (let i = 0; i < N; i++) {
        const name = readlineSync.question("Enter name: ");
        const phone = readlineSync.question("Enter phone: ");
        const bday = readlineSync.question("Enter birthday (day month year): ").split(' ').map(Number);
        BLOCKNOTE.push(new Note(name, phone, bday));
    }

    // Виводимо дані про людей в яких співпадають місяці
    const month = parseInt(readlineSync.question("Enter month: "), 10);
    BLOCKNOTE.forEach(note => {
        if (month === note.bday[1]) {
            console.log(`${note.name} ${note.phone} ${note.bday[0]} ${note.bday[1]} ${note.bday[2]}`);
        }
    });
}

module.exports = { information };