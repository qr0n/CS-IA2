import subprocess
from textwrap import dedent

# Function to run the C code with different scenarios
def run_c_code(test_input):
    result = subprocess.run(["gcc", "main.c", "-o", "main.exe"])
    if result.returncode == 0:
        process = subprocess.run(["./main.exe"], input=test_input, text=True, capture_output=True)
        return process.stdout
    else:
        return "Compilation Error"

# Function to generate formatted Markdown for test results
def generate_markdown(title, input_description, input_data_1, input_data_2, expected_output, actual_output):
    with open("results.md", "a") as results:
        markdown = dedent(f"""
        ## {title}

        **Input Description:**
        {input_description}

        **Input Data 1:**
        ```
        {input_data_1}
        ```

        **Input Data 2:**
        ```
        {input_data_2}
        ```

        **Expected Output:**
        ```
        {expected_output}
        ```

        **Actual Output:**
        ```
        {actual_output}
        ```
    """)
        results.write(markdown)
    return markdown

# Test scenarios
# Test scenarios
test_scenarios = [
    {"title": "Normal Scenario", "input_1": "username", "input_2": "password", "expected_output": "User created"},
    {"title": "Extreme Scenario", "input_1": "Us34N4m3", "input_2": "P$ssW0R1", "expected_output": "User created"},
    {"title": "Erroneous Scenario", "input_1": "1", "input_2": "2", "expected_output": "User created"}
]

# Generate and print Markdown for each scenario
for scenario in test_scenarios:
    input_description = "Describe the input data for " + scenario["title"]
    actual_output = run_c_code(f"{scenario['input_1']}\n{scenario['input_2']}")
    markdown = generate_markdown(scenario["title"], input_description, scenario["input_1"], scenario["input_2"], scenario["expected_output"], actual_output)
    print(markdown)
