const { main } = require('../src/test2');
const readlineSync = require('readline-sync');

jest.mock('readline-sync');

describe('Main Function End-to-End Test', () => {
    beforeEach(() => {
        jest.clearAllMocks();
        global.console.log = jest.fn();
    });

    test('should run in automatic mode', () => {
        readlineSync.question.mockReturnValueOnce('1');
        main();
        expect(global.console.log).toHaveBeenCalledWith(expect.stringContaining("Початок роботи"));
        expect(global.console.log).toHaveBeenCalledWith(expect.stringContaining("Книга1"));
        expect(global.console.log).toHaveBeenCalledWith(expect.stringContaining("Lenovo"));
        expect(global.console.log).toHaveBeenCalledWith(expect.stringContaining("Яблуко"));
        expect(global.console.log).toHaveBeenCalledWith(expect.stringContaining("Кінець роботи"));
    });

    test('should handle invalid choice', () => {
        readlineSync.question.mockReturnValueOnce('3');
        main();
        expect(global.console.log).toHaveBeenCalledWith(expect.stringContaining("Невірний вибір"));
    });
});