const { information } = require('../src/test1');

describe('information', () => {
    beforeEach(() => {
        global.console.log = jest.fn();
    });

    it('should collect and display notes with matching month', () => {
        const mockPrompts = [
            "Alice", "12345", "1 5 1990",
            "Bob", "67890", "2 5 1985",
            "Charlie", "54321", "3 6 1992",
            "David", "98765", "4 7 1980",
            "Eve", "11111", "5 5 1975",
            "Frank", "22222", "6 8 1995",
            "Grace", "33333", "7 9 1988",
            "Hank", "44444", "8 10 1991",
            "Ivy", "55555", "9 11 1983",
            "Jack", "66666", "10 12 1990",
            "5" // Місяць для пошуку
        ];

        jest.spyOn(require('readline-sync'), 'question').mockImplementation(() => mockPrompts.shift());

        information();

        expect(global.console.log).toHaveBeenCalledWith("Alice 12345 1 5 1990");
        expect(global.console.log).toHaveBeenCalledWith("Bob 67890 2 5 1985");
        expect(global.console.log).toHaveBeenCalledWith("Eve 11111 5 5 1975");
    });
});