# Import the os module for system operations (like clearing the screen)
import os
# Import the sys module to exit the program or to pass a command line argument
import sys
# Import the time module for time-related functions
import time

# Import the Grid class to manage the game grid
from grid import Grid

def print_menu(grid):
    """Print the game menu and get user input with validation."""
    menu = [
        "",
        "1. Let me select two elements",
        "2. Uncover one element for me",
        "3. I give up - reveal the grid",
        "4. New game",
        "5. Exit",
        ""
    ]
    
    # Print each option in the menu
    for option in menu:
        print(option)

    # Get user input and handle validation
    try:
        # Get the user's choice and convert to integer
        choice = int(input("Select: "))
        # Match the user's choice to different game actions
        match choice:
            case 1:
                # If the game is already over
                if grid.all_cells_revealed():
                    # Clear the screen
                    os.system("clear");
                    # Print the grid
                    grid.print_grid()
                    print("Please start a new game to use option 1.")
                else:
                    print("You selected: Let me select two elements")
                    # Handle selecting two elements
                    handle_select_two_elements(grid)
            case 2:
                # If the game is already over
                if grid.all_cells_revealed():
                    # Clear the screen
                    os.system("clear");
                    # Print the grid
                    grid.print_grid()
                    print("Please start a new game to use option 2.")
                else:
                    print("You selected: Uncover one element for me")
                    # Handle uncovering one element
                    handle_uncover_one_element(grid)
            case 3:
                # If the game is already over
                if grid.all_cells_revealed():
                    # Clear the screen
                    os.system("clear");
                    # Print the grid
                    grid.print_grid()
                    print("Please start a new game to use option 3.")
                else:
                    # Clear the screen
                    os.system("clear");
                    # Reveal the entire grid
                    grid.reveal_all_cells()
                    # Print the grid to show all values
                    grid.print_grid()
                    print("You selected: I give up - reveal the grid")
            case 4:
                # Clear the screen
                os.system("clear")
                # Reset the grid for a new game
                grid.reset_grid()
                # Print the new grid with hidden cells
                grid.print_grid()
                print("You selected: New game")
            case 5:
                print("Exiting the game. Goodbye!")
                # Exit the program
                sys.exit()
            case _:
                print("Invalid choice, please select a number between 1 and 5.")
                
    # Handle invalid input
    except ValueError:
        # Prompt for valid input
        print("Please enter a valid number.")

def handle_select_two_elements(grid):
    """Handle the selection of two elements by the player."""
    try:
        # Ask for the first cell, check if it's part of a match (if it is, ask again)
        while True:
            # Get coordinates for the first cell
            cell1 = get_cell_coordinates(grid)

            # Check if the first cell is part of a match (Option 1)
            if grid.get_cell(cell1[0], cell1[1]).match_revealed:
                print("The first cell is part of a match and cannot be selected. Please select a different cell.")
                # Keep asking for the first cell until it's valid
                continue
            else:
                # Exit the loop if the first cell is valid
                break

        # Get the second cell
        while True:
            # Get coordinates for the second cell
            cell2 = get_cell_coordinates(grid)
            
            # Check if the second cell is part of a match (Option 1)
            if grid.get_cell(cell2[0], cell2[1]).match_revealed:
                print("The second cell is part of a match and cannot be selected. Please select a different cell.")
                # Ask for a different second cell
                continue
            
            # Check if both cells are revealed (prohibited case)
            if grid.get_cell(cell1[0], cell1[1]).permanently_revealed and grid.get_cell(cell2[0], cell2[1]).permanently_revealed:
                print(f"You already selected a revealed cell. Please select a hidden cell.")
                # Ask for a different second cell
                continue
            
            # Check if the two selected cells are the same
            if cell1 == cell2:
                print("You cannot select the same cell twice. Please choose another cell.")
            else:
                # Exit the loop if the second cell is valid
                break
        
        # Reveal the cells temporarily only if they are not permanently revealed using Option 2 or part of a match using Option 1
        if not grid.get_cell(cell1[0], cell1[1]).permanently_revealed:
            # Reveal the first cell
            grid.reveal_cell(cell1[0], cell1[1])
        if not grid.get_cell(cell2[0], cell2[1]).permanently_revealed:
            # Reveal the second cell
            grid.reveal_cell(cell2[0], cell2[1])
        
        # Clear the screen
        os.system("clear")
        # Print the grid to show the revealed cells
        grid.print_grid()

        # Check if the two cells match
        if grid.is_pair(grid.get_cell(cell1[0], cell1[1]), grid.get_cell(cell2[0], cell2[1])):
            # Inform the user it's a match
            print("It's a match!")
            # Mark the matched cells as revealed due to a match
            grid.get_cell(cell1[0], cell1[1]).match_revealed = True
            grid.get_cell(cell2[0], cell2[1]).match_revealed = True
        else:
            print("Not a match. Try again.")
            # Pause for 2 seconds to show the numbers
            time.sleep(2)

            # Clear the console and hide the numbers again
            os.system("clear")

            # Hide the cells only if they were temporarily revealed
            if not grid.get_cell(cell1[0], cell1[1]).permanently_revealed:
                # Hide the first cell again
                grid.hide_cell(cell1[0], cell1[1])
            if not grid.get_cell(cell2[0], cell2[1]).permanently_revealed:
                # Hide the second cell again
                grid.hide_cell(cell2[0], cell2[1])

            # Print the grid again with the hidden cells
            grid.print_grid()
        
        # Track the guess and check if the game is won
        score = grid.make_guess(grid.get_cell(cell1[0], cell1[1]), grid.get_cell(cell2[0], cell2[1]), option=1)
        # If the game is won (score is calculated)
        if score is not None:
            # Show the final score
            print(f"Congratulations, you won! You found all the pairs! Your score is: {score:.1f} (⌐■_■)")
            
    except ValueError:
        # Handle invalid input for cell coordinates
        print("Invalid cell coordinates. Please try again.")


def handle_uncover_one_element(grid):
    """Allow the player to uncover a single element."""    
    try:
        # Get coordinates of the cell to uncover
        cell = get_cell_coordinates(grid)

        # If the cell is already revealed or part of a match
        if grid.get_cell(cell[0], cell[1]).permanently_revealed or grid.get_cell(cell[0], cell[1]).match_revealed:
            # Clear the screen
            os.system("clear")
            # Print the grid
            grid.print_grid()
            # Exit the function early, no guess is added    
            return
        
        # Reveal the selected cell permanently if not already revealed or not part of a match
        if not grid.get_cell(cell[0], cell[1]).permanently_revealed and not grid.get_cell(cell[0], cell[1]).match_revealed:
            # Reveal the cell permanently
            grid.reveal_cell(cell[0], cell[1])
            # Mark this as permanently revealed
            grid.get_cell(cell[0], cell[1]).permanently_revealed = True
        
        # Clear the screen
        os.system("clear")
        # Print the grid with the revealed chosen cell
        grid.print_grid()
        
        # Track the guess (counts as two guesses) and check if the game is won
        score = grid.make_guess(grid.get_cell(cell[0], cell[1]), grid.get_cell(cell[0], cell[1]), option=2)
        # If no valid guesses were made
        if score == 0:
            print("You cheated, your score is 0! (╯° °)╯ ┻━┻")
        # If the game is won (score is calculated)
        elif score is not None:
            print(f"Congratulations! You've uncovered all pairs! Your score is: {score:.1f}")
            
    except ValueError:
        # Handle invalid input for cell coordinates
        print("Invalid cell coordinates. Please try again.")


def get_cell_coordinates(grid):
    """Get the coordinates of a cell from the player."""
    while True:
        try:
            # Get user input and convert to uppercase
            cell_input = input("Enter the cell coordinates (e.g., A0): ").upper()

            # Ensure the input is valid (column letter + row number)
            if len(cell_input) < 2:
                print("Invalid input. Please enter coordinates in the format A0.")
                # Retry if the input is invalid
                continue

            # The letter represents the column
            column_letter = cell_input[0]
            # The rest is the row number
            row_number = cell_input[1:]

            # Validate column letter and convert to column index (0-indexed)
            # Dynamically valid column range
            if 'A' <= column_letter <= chr(ord('A') + grid.size - 1):
                # [A] -> [0], [B] -> [1], ..., etc.
                column = ord(column_letter.upper()) - ord('A')
            else:
                print(f"Invalid column. Please enter a letter between A and {chr(ord('A') + grid.size - 1)}.")
                # Retry if the column letter is invalid
                continue

            # Validate row number and convert to row index (0-indexed)
            try:
                # Keep as integer without subtracting 1
                row = int(row_number)
                # Ensure the row is within valid bounds
                if row < 0 or row >= grid.size:
                    print(f"Invalid row. Please enter a row number between 0 and {grid.size - 1}.")
                    # Retry if the row is invalid
                    continue
            except ValueError:
                print(f"Invalid row. Please enter a number between 0 and {grid.size - 1}.")
                # Retry if the row is not a valid number
                continue

            # If everything is valid, return the row and column
            return row, column
        except Exception as e:
            print(f"Error: {e}")
            # Retry on any exception
            continue

def main():
    # Check if a command-line argument for grid size is provided and valid
    if len(sys.argv) != 2 or not sys.argv[1].isdigit() or int(sys.argv[1]) not in {2, 4, 6}:
        print("Error: Please specify a grid size of 2, 4, or 6 as a command-line argument.")
        sys.exit(1)  # Exit with error code

    # Parse the grid size from the command-line argument
    size = int(sys.argv[1])
    
    # Clear the screen
    os.system("clear")
    # Initialize the game grid with the specified size
    grid = Grid(size)
    
    # Print the initial hidden grid
    grid.print_grid()

    # Loop to keep the menu active until the user chooses to exit
    while True:
        # Display the menu and let the user interact with the game
        print_menu(grid)

# Start the game by calling the main function
if __name__ == "__main__":
    main()