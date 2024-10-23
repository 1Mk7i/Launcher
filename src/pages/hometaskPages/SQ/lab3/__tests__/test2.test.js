const { Product } = require('../src/test2');
const readlineSync = require('readline-sync');

jest.mock('readline-sync');

describe('Product Class Integration Tests', () => {
    beforeEach(() => {
        jest.clearAllMocks();
        global.console.log = jest.fn();
    });

    test('should create a product and get info', () => {
        const product = new Product("Test Product", 100, ["test", "product"]);
        product.getInfo();
        expect(global.console.log).toHaveBeenCalledWith(expect.stringContaining("Test Product"));
        expect(global.console.log).toHaveBeenCalledWith(expect.stringContaining("100"));
        expect(global.console.log).toHaveBeenCalledWith(expect.stringContaining("test product"));
    });

    test('should add and remove keywords', () => {
        const product = new Product("Test Product", 100, ["test"]);
        product.addKeyword("new");
        expect(product.keywords).toContain("new");
        product.removeKeyword("test");
        expect(product.keywords).not.toContain("test");
    });

    test('should find product by keyword', () => {
        const product = new Product("Test Product", 100, ["test"]);
        product.findKeyword("test");
        expect(global.console.log).toHaveBeenCalledWith(expect.stringContaining("Test Product"));
    });

    test('should show next ID', () => {
        Product.showNextID();
        expect(global.console.log).toHaveBeenCalledWith(expect.stringContaining("Наступний ID"));
    });
});