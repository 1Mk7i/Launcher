// Інтеграційний тест

const { getData, processData } = require('../src/dataProcessor');

test('processes data correctly', () => {
  const data = getData();
  
  // Обработка даних
  const result = processData(data);
  
  // Очікуваний результат
  const expectedResult = 'expectedResult';
  
  // Перевірка результату
  expect(result).toBe(expectedResult);
});