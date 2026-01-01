with open('input', 'r', encoding='utf-8') as file:
    file_lines = file.readlines()

ranges = []

while True:
    # parse ranges until empty line
    line = file_lines.pop(0).strip()
    if not line:
        break
    start, end = line.split("-")
    start, end = int(start), int(end)
    ranges.append((start, end))

# part 1
n_fresh_ingredients = 0

for line in file_lines:
    ingredient_id = int(line)

    for start, end in ranges:
        if start <= ingredient_id <= end:
            n_fresh_ingredients += 1
            break

print(n_fresh_ingredients)

# part 2
def merge_ranges(ranges:list) -> list:
    ranges.sort()
    merged = []
    current_start, current_end = ranges[0]

    for start, end in ranges[1:]:
        if start <= current_end + 1:
            current_end = max(current_end, end)
        else:
            merged.append((current_start, current_end))
            current_start, current_end = start, end

    merged.append((current_start, current_end))
    return merged

ranges = merge_ranges(ranges)

included_ids = sum(end - start + 1 for start, end in ranges)

print(included_ids)