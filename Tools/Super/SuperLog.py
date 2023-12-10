counter = 0
total_amount = 0

with open('change_log.txt', 'r') as file:
    lines = file.readlines()
    for line_number, line in enumerate(lines, start=1):
        if line.startswith("2"):
            # Count the occurrences of the phrase 'amount of times' in each line
            amount_count = line.count("amount of times")
            if amount_count > 0:
                total_amount += amount_count
            counter += 1

    print(f"-- Found {counter} Classes that implement 'Super'")
    print(f"-- Keyword Super modified {total_amount} times")