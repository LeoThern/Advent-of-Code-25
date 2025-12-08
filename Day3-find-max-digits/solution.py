def find_highest_joltage(bank:list, len=2):
    if len == 1:
        return max(bank)
    largest_digit = max(bank[:-(len-1)])
    left_most_index = bank.index(largest_digit)
    highest_joltage = int(
        str(largest_digit) + str(find_highest_joltage(bank[left_most_index+1:], len-1))
    )
    return highest_joltage

with open('input', 'r', encoding='utf-8') as file:
    banks = file.readlines()

total_joltage = 0

for bank in banks:
    bank = [int(i) for i in bank.strip()]
    total_joltage += find_highest_joltage(bank)

print(total_joltage)


total_joltage = 0

for bank in banks:
    bank = [int(i) for i in bank.strip()]
    total_joltage += find_highest_joltage(bank, len=12)

print(total_joltage)