# Fetch Coding Exercise - Software Engineering Internship

The problem is to calculate the way to spend points based on transactions history. The transactions are recorded in a CSV file, including the payer, number of points, and timestamp of each transaction. The goal is to maximize the number of points spent by subtracting the minimum number of points earned.



## Input

- The amount of points to spend: An integer, representing the total number of points to be spent.
- `transactions.csv`: A comma-separated file, with each line representing a transaction, including the following columns:
  - Payer: A string, representing the payer of the points.
  - Points: An integer, representing the number of points.
  - Timestamp: A string, representing the time the transaction was made, in the format of YYYY-MM-DDTHH:MM:SSZ.



## Output

- A table, showing the remaining points of each payer after all transactions have been processed.
- If the input file is invalid, an error message will be shown and the program will terminate.



## Usage

### Requirement

- g++

### Compilation

To compile, navigate to the directory and type `make`:

```cpp
git clone git@github.com:JuhuaZhang/Fetch-Coding-Exercise.git
cd Fetch-Coding-Exercise
make
```

### Example

Input:

```bash
./main 5000
```

Output:

```
DANNON: 1000
MILLER COORS: 5300
UNILEVER: 0
```
