# Import the random module for randomizing the hidden values
import random

class Cell:
    def __init__(self, value):
        """Initialize the cell with a value and hidden state."""
        # The value of the cell (number)
        self.value = value
        # Cell is hidden initially
        self.hidden = True
        # Revealed by Option 2
        self.permanently_revealed = False
        # Revealed because of a match (Option 1)
        self.match_revealed = False

    def reveal(self):
        """Reveal the cell."""
        # Set the cell's hidden status to False
        self.hidden = False

    def hide(self):
        """Hide the cell again."""
        # Set the cell's hidden status back to True
        self.hidden = True

    def __str__(self):
        """String representation of the cell (either 'X' or the number)."""
        # Show 'X' if hidden, otherwise the cell value
        return 'X' if self.hidden else str(self.value)

class Grid:
    def __init__(self, size):
        """Initialize the grid with a given size."""
        # Grid size (number of rows/columns)
        self.size = size
        # Create the grid structure (2D list)
        self.grid = self.create_grid()
        # List of hidden values for the grid
        self.hidden_values = self.create_hidden_values()
        # Populate the grid with cells containing values
        self.populate_grid()
        # Track the number of guesses made
        self.guesses = 0

    def create_grid(self):
        """Create a 2D list for the grid."""
        # Initialize a 2D grid with None
        return [[None for _ in range(self.size)] for _ in range(self.size)]

    def create_hidden_values(self):
        """Create pairs of integers to hide in the grid."""
        # Number of pairs needed (half the grid size)
        num_pairs = (self.size * self.size) // 2
        # Create two instances of each number for pairs
        values = [i for i in range(num_pairs)] * 2
        # Shuffle the values randomly
        random.shuffle(values)
        # Return the shuffled list of hidden values
        return values

    def populate_grid(self):
        """Populate the grid with pairs of numbers."""
        # Index to track where to place values
        idx = 0
        # Loop through each row
        for row in range(self.size):
            # Loop through each column
            for col in range(self.size):
                 # Assign a new cell with a value
                self.grid[row][col] = Cell(self.hidden_values[idx])
                # Move to the next value in the hidden_values list
                idx += 1

    def print_grid(self):
        """Print the title centered within a specified width, framed by vertical bars."""
        # Title of the game
        title = "Brain Buster"
        # Width of the printed grid header
        width = 30
        # Total padding (subtract 2 for the bars on each side)
        padding_total = width - len(title) - 2
        # Left padding
        left_padding = padding_total // 2
        # Right padding
        right_padding = padding_total - left_padding
        
        # Print dashed lines at the top line of the title
        print('-' * (width))
        # Print the title
        print("|" + " " * left_padding + title + " " * right_padding + "|")
        # Print dashed lines at the bottom line of the title
        print('-' * (width) + "\n")
    
        """Print the grid with row and column labels."""
        # Calculate the maximum value in the grid to determine cell width for printing
        max_value = max(cell.value for row in self.grid for cell in row)
        # Width of each cell, based on the largest value
        cell_width = len(str(max_value)) + 1
        
        # If the grid is small, ensure that each cell is at least 3 characters wide
        if self.size <= 4:
            cell_width = max(cell_width, 3)

        # Print column labels ([A], [B], [C], ...)
        print("     " + "  ".join(f"[{chr(65 + i)}]{' ' * (cell_width - 2)}" for i in range(self.size)))  # Column labels

        # Print each row of the grid with appropriate formatting
        for idx, row in enumerate(self.grid):
            # Print row labels on the left ([0], [1], [2], ...)
            print(f"[{idx:>{len(str(self.size))}}] ", end="")
            for cell in row:
                # Print each cell with padding
                print(f"{str(cell):>{cell_width}}", end="   ")
            # Move to the next line after each row
            print()

    def reveal_cell(self, row, col):
        """Reveal a specific cell in the grid."""
        # Set the specific cell to 'revealed'
        self.grid[row][col].reveal()

    def hide_cell(self, row, col):
        """Hide a specific cell in the grid, but only if it's not permanently revealed."""
        # Don't hide cells permanently revealed from processing Option 2
        if not self.grid[row][col].permanently_revealed:
            # Set the specific cell to 'hidden'
            self.grid[row][col].hide()

    def is_pair(self, cell1, cell2):
        """Check if two cells match (if both reveal the same number)."""
        # Return True if the values match, else False
        return cell1.value == cell2.value

    def get_cell(self, row, col):
        """Get a specific cell from the grid."""
        # Return the cell at the given coordinates
        return self.grid[row][col]

    def reveal_all_cells(self):
        """Reveal all cells in the grid."""
        # Loop through each row
        for row in range(self.size):
            # Loop through each column
            for col in range(self.size):
                # Set the cell as permanently revealed
                self.grid[row][col].permanently_revealed = True
                # Reveal the cell (in case it was hidden)
                self.grid[row][col].reveal()

    def reset_grid(self):
        """Reset the grid for a new game."""
        # Recreate the grid
        self.grid = self.create_grid()
        # Generate new hidden values
        self.hidden_values = self.create_hidden_values()
        # Populate the grid with new cells
        self.populate_grid()
        # Reset the guess count
        self.guesses = 0
        
    def calculate_minimum_guesses(self):
        """Calculate the minimum number of guesses required for the game."""
        # Calculate the total number of cells in the grid
        total_cells = len(self.grid) * len(self.grid[0])
        # Each guess reveals 2 cells, so divide by 2
        return total_cells // 2

    def make_guess(self, cell1, cell2, option):
        """Handle a guess and check if all pairs are matched."""
        # Selecting two elements counts as one guess
        if option == 1:
            # Increment the guess count by 1
            self.guesses += 1
        # Uncovering one element counts as two guesses
        elif option == 2:
            # Increment the guess count by 2
            self.guesses += 2
            
        # Calculate the minimum possible guesses required
        min_guesses = self.calculate_minimum_guesses()

        # Check if all cells are not hidden
        if self.all_cells_revealed():
            # If all cells are not revealed by using Option 2, calculate score
            if not self.is_fully_revealed():
                # Calculate score based on guesses
                score = (min_guesses / self.guesses) * 100
                return score
            # Return 0 if all cells are revealed by using Option 2
            return 0
        # Game is not won yet
        return None
        
    def is_fully_revealed(self):
        """Check if all cells in the grid are permanently revealed."""
        # Check if all cells are permanently revealed by using Option 2
        return all(cell.permanently_revealed for row in self.grid for cell in row)
    
    def all_cells_revealed(self):
        """Check if all cells are either match_revealed or revealed."""
        # Check if all cells are revealed using Option 2 or part of a match found using Option 1
        return all(cell.match_revealed or cell.permanently_revealed for row in self.grid for cell in row)
