const readlineSync = require('readline-sync');

const colors = {
    red: "\x1b[31m",
    green: "\x1b[32m",
    yellow: "\x1b[33m",
    blue: "\x1b[34m",
    magenta: "\x1b[35m",
    cyan: "\x1b[36m",
    reset: "\x1b[0m"
};

class Product {
    static nextID = 100000;

    constructor(name = '', price = 0, keywords = []) {
        this.id = Product.generateID();
        this.name = name;
        this.price = price;
        this.keywords = keywords;
    }

    static generateID() {
        return this.nextID++;
    }

    static showNextID() {
        console.log(`${colors.magenta}Наступний ID: ${colors.yellow}${this.nextID}${colors.reset}`);
    }

    getID() {
        return this.id;
    }

    getInfo() {
        console.log(`${colors.blue}ID: ${colors.yellow}${this.id}${colors.reset}`);
        console.log(`${colors.blue}Назва: ${colors.yellow}${this.name}${colors.reset}`);
        console.log(`${colors.blue}Ціна: ${colors.yellow}${this.price}${colors.reset}`);
        console.log(`${colors.blue}Ключові слова: ${colors.yellow}${this.keywords.join(' ')}${colors.reset}`);
    }

    findKeyword(keyword) {
        if (this.keywords.includes(keyword)) {
            this.getInfo();
        }
    }

    setName(newName) {
        this.name = newName;
    }

    getName() {
        return this.name;
    }

    setPrice(newPrice) {
        this.price = newPrice;
    }

    getPrice() {
        return this.price;
    }

    addKeyword(keyword) {
        this.keywords.push(keyword);
    }

    removeKeyword(keyword) {
        this.keywords = this.keywords.filter(key => key !== keyword);
    }

    Interface() {
        console.clear();
        console.log(`${colors.green}______________________________________________________${colors.reset}`);
        console.log(`${colors.green}1. Додати товар${colors.reset}`);
        console.log(`${colors.green}2. Видалити товар${colors.reset}`);
        console.log(`${colors.green}3. Пошук товару${colors.reset}`);
        console.log(`${colors.green}4. Вивести інформацію про товар${colors.reset}`);
        console.log(`${colors.green}5. Вивести всі товари${colors.reset}`);
        console.log(`${colors.green}6. Вийти${colors.reset}`);

        const choice = parseInt(readlineSync.question(''), 10);
        if (choice === 1) {
            const name = readlineSync.question(`${colors.cyan}Введіть назву товару: ${colors.reset}`);
            const price = parseFloat(readlineSync.question(`${colors.cyan}Введіть ціну товару: ${colors.reset}`));
            const n = parseInt(readlineSync.question(`${colors.cyan}Введіть кількість ключових слів: ${colors.reset}`), 10);
            const keywords = [];
            for (let i = 0; i < n; i++) {
                const keyword = readlineSync.question(`${colors.cyan}Введіть ключове слово: ${colors.reset}`);
                keywords.push(keyword);
            }
            const newProduct = new Product(name, price, keywords);
            newProduct.Interface();
        } else if (choice === 2) {
            const id = parseInt(readlineSync.question(`${colors.cyan}Введіть ID товару: ${colors.reset}`), 10);
            if (id === this.getID()) {
                console.log(`${colors.red}Неможливо видалити поточний товар${colors.reset}`);
            } else {
                console.log(`${colors.red}Товар з ID ${id} не знайдено${colors.reset}`);
            }
            this.Interface();
        } else if (choice === 3) {
            const keyword = readlineSync.question(`${colors.cyan}Введіть ключове слово: ${colors.reset}`);
            this.findKeyword(keyword);
            this.Interface();
        } else if (choice === 4) {
            this.getInfo();
            this.Interface();
        } else if (choice === 5) {
            console.log(`${colors.red}Немає збережених товарів${colors.reset}`);
            this.Interface();
        } else if (choice === 6) {
            return;
        } else {
            console.log(`${colors.red}Невірний вибір${colors.reset}`);
            this.Interface();
        }
    }
}

function main() {
    console.log(`${colors.blue}Початок роботи${colors.reset}`);
    console.log(`${colors.green}Варіанти роботи програми:${colors.reset}`);
    console.log(`${colors.green}1. Автоматичний${colors.reset}`);
    console.log(`${colors.green}2. Ручний${colors.reset}`);
    const choice = parseInt(readlineSync.question(''), 10);

    if (choice === 1) {
        const product1 = new Product("Книга1", 100, ["Книга"]);
        const product2 = new Product("Lenovo", 1000, ["Комп'ютер"]);
        const product3 = new Product("Яблуко", 5, ["Їжа"]);

        product1.getInfo();
        product2.getInfo();
        product3.getInfo();

        console.log(`${colors.cyan}Пошук за ключовим словом 'Комп'ютер':${colors.reset}`);
        product2.findKeyword("Комп'ютер");

        product1.setName("Книга2");
        product1.setPrice(200);

        product1.addKeyword("Художня");
        product1.removeKeyword("Книга");

        product1.getInfo();

        Product.showNextID();
    } else if (choice === 2) {
        const product = new Product();
        product.Interface();
    } else {
        console.log(`${colors.red}Невірний вибір${colors.reset}`);
    }

    console.log(`${colors.red}Кінець роботи${colors.reset}`);
}

if (require.main === module) {
    main();
}

module.exports = { Product, main };