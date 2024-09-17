# Kevin Caballero
# Date: 12/04/2022
# Text Based Game

def show_instructions():

    # Prints a main menu with available commands and objective
    print("\nTroll Text Adventure Game")
    print("Collect at least 6 items to defend the grand hall or be killed by the troll!")
    print("Move Commands: go South, go North, go East, go West")
    print("To add to inventory: get 'item in room'\n")
    print("Command to exit the game: exit")


def show_player_status(current_room, inventory, rooms):

    # Prints the player's inventory, room, and available items within the room
    print("Your are in the: ", current_room)
    print("Inventory: ", inventory)
    if len(rooms[current_room]['item']) > 0:
        print("You see", rooms[current_room]['item'])
    print("---------------------------")


def main():

    # Defines an inventory that is initially empty
    # Defines a dictionary linking all the available rooms and items contained
    rooms = {
        'Barracks': {'North': 'Old Temple', 'South': 'Blacksmith', 'West': 'Farms', 'East': 'Training Grounds', 'item': ''},
        'Old Temple': {'North': 'Grand Hall', 'South': 'Barracks', 'item': 'Scroll'},
        'Farms': {'East': 'Barracks', 'item': 'Bread'},
        'Blacksmith': {'North': 'Barracks', 'South': 'Medicine Hut', 'item': 'Armor'},
        'Medicine Hut': {'North': 'Blacksmith', 'item': 'Medicinal Herbs'},
        'Training Grounds': {'North': 'Armory', 'South': 'Shipyard', 'West': 'Barracks', 'item': 'Bow and Arrows'},
        'Shipyard': {'North': 'Training Grounds', 'item': 'Rope'},
        'Armory': {'South': 'Training Grounds', 'item': 'Axe'},
        'Grand Hall': {'South': 'Old Temple', 'item': 'Troll'}
    }

    inventory = []

    current_room = 'Barracks'

    # Displays the game's instructions
    show_instructions()

    while True:

        # Calls the function to show the player's current room, inventory, and any item present in their current room
        show_player_status(current_room, inventory, rooms)

        # Receives the player's next move
        next_move = tuple(input("Enter your next move: ").split())

        # Exits the game if the player decides to
        # Checks if input is valid
        if next_move[0] == 'exit':
            print("You have exited the game")
            break
        elif len(next_move) < 2:
            print("Invalid input, try again")

        # Obtains player's next move
        if next_move[0] == 'go':
            if next_move[1] in rooms[current_room]:
                current_room = rooms[current_room][next_move[1]]
            elif next_move[1] is not rooms[current_room]:
                print("You can't go that way!")

        # Identifies items in the room
        # Also checks player's inventory for pickup
        # Otherwise prompts the player that item is already in inventory
        if next_move[0] == 'get':
            if next_move[1] in rooms[current_room]['item']:
                inventory.append(rooms[current_room]['item'])
                rooms[current_room]['item'] = ''
                print(next_move[1], "acquired!")
            elif next_move[1] in inventory:
                print(next_move[1], "is already in your inventory")

        # Checks if player has all required items otherwise game is over or grants victory if player has required items
        if current_room == 'Grand Hall':
            if len(inventory) < 6:
                print("GAME OVER")
                print("Thanks for playing!  Exit the game whenever you're ready.")
                rooms[current_room]['item'] = ''
                inventory = []
            else:
                print("You defeated the troll! Good Job!")
                print("Thanks for playing! Exit the game whenever you're ready.")
                rooms[current_room]['item'] = ''
                inventory = []


# Calls the 'main' function to run the text-based game
main()
