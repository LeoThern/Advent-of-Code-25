with open('input', 'r') as file:
    ranges = file.read().split(',')
    ranges = [r.split('-') for r in ranges]
    ranges = [(int(s), int(e)) for s, e in ranges]

sum_invalid_ids_1 = 0
sum_invalid_ids_2 = 0

for start, end in ranges:
    for id in range(start, end + 1):
        id = str(id)
        if id[:len(id)//2] == id[len(id)//2:]:
            sum_invalid_ids_1 += int(id)
        for divisor in [i for i in range(1, len(id)) if len(id) % i == 0]:
            parts = [id[i:i+divisor] for i in range(0, len(id), divisor)]
            if len(set(parts)) == 1:
                sum_invalid_ids_2 += int(id)
                print(id, parts)
                break # some invalid ids match multiple divisors

print(sum_invalid_ids_1)
print(sum_invalid_ids_2)
