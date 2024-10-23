money = 7100
money2 = 8950

def podatok(money):
    if money >= 10000:
        a = money - 1000
        b = a * 0.05
        a = money - 7000
        a = a * 0.2
        money = a + b
        return money
    if money >= 7000:
        a = money - 1000
        b = a * 0.05
        a = money - 7000
        a = a * 0.2
        money = a + b
        return money
    if money >= 1000:
        a = money - 1000
        a = a / 20
        return money - a
    return money
    
print("Task 1: ","Input: ", money,"Output: ", podatok(money))
