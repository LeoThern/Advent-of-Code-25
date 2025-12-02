with open('input', 'r', encoding='utf-8') as file:
    instructions = file.readlines()

dial_state, zero_states, zero_movements = 50, 0, 0

for line in instructions:
    # get instruction
    op, n = line[0], int(line[1:])
    match op:
        case 'L':
            movements = [-1] * n
        case 'R':
            movements = [+1] * n
        case _:
            raise ValueError(f"unknown operation '{op}'")

    # apply instruction with single steps
    for movement in movements:
        dial_state += movement
        if dial_state == -1:
            dial_state = 99
        if dial_state == 100:
            dial_state = 0

        if dial_state == 0:
            zero_movements += 1

    if dial_state == 0:
        zero_states += 1

print(zero_states)
print(zero_movements)