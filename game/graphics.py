import pygame
import os

# Initialize Pygame
pygame.init()

# Set up the display
width, height = 1000, 1000
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption("Tic-Tac-Toe")

# Load images
bg = pygame.image.load('xo/S.png')
x = pygame.image.load('xo/x.png')
o = pygame.image.load('xo/o.png')
_1 = pygame.image.load('xo/1.png')
_2 = pygame.image.load('xo/2.png')
_0 = pygame.image.load('xo/0.png')

# Resize images to fit the grid
bg = pygame.transform.scale(bg, (width, height))
x = pygame.transform.scale(x, (width // 10, height // 10))
o = pygame.transform.scale(o, (width // 10, height // 10))
_1 = pygame.transform.scale(_1, (width // 2, height // 7))
_2 = pygame.transform.scale(_2, (width // 2, height // 7))
_0 = pygame.transform.scale(_0, (width // 2, height // 7))

def draw_board(board):
    screen.blit(bg, (0, 0))
    for i in range(3):
        for j in range(3):
            if j >= len(board[i]):
                continue  # Skip if this row doesn't have enough columns
            
            # Calculate the position to draw the image
            x_pos = 250 + j * (width // 5.5)
            y_pos = 250 + i * (height // 7.8)
            
            if board[i][j] == 'X':
                screen.blit(x, (x_pos, y_pos))
            elif board[i][j] == 'O':
                screen.blit(o, (x_pos, y_pos))


def read_game_state(filename):
    try:
        with open(filename, "r") as file:
            lines = file.readlines()
        
        board = []
        for line in lines[:3]:  # Only take the first three lines for the board
            chars = [char for char in line]
            board.append(chars)
        
        result = None
        if len(lines) > 3:
            result = lines[3].strip()
        
        return board, result
    except FileNotFoundError:
        print("Game state file not found.")
        return [], None
    except Exception as e:
        print(f"Error reading game state: {e}")
        return [], None

def main():
    clock = pygame.time.Clock()
    running = True
    game_over = False
    
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
        
        board, result = read_game_state("gamestate.txt")
        draw_board(board)
        
        if result:
            if "1" in result:
                screen.blit(_1, (250, 650))
            elif "2" in result:
                screen.blit(_2, (250, 650))
            else:
                screen.blit(_0, (250, 650))
            game_over = True
        
        pygame.display.flip()
        clock.tick(30)  # Limit the frame rate to 30 FPS

    pygame.quit()

if __name__ == "__main__":
    main()

       
