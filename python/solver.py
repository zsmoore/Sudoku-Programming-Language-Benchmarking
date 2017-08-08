import sys
import pprint
import math

SIZE = None

''' Loads from file into a 2d array representing a sudoku board '''
def load_file(filename):
    global SIZE
    inData = open(filename, "r")
    board = []

    for line in inData.readlines():
        dimension = line.split()
        SIZE = len(dimension)
        try:
            board.append(list(map(int, dimension)))
        except ValueError as e:
            print("Incorrect input: Unable to convert input to integer")
            exit()       
    return board

'''
    Functions Used To Check Board
'''
''' Check whether we can put a number in a spot '''
def check_safe(board, row, col, num):
    return (not in_row(board, row, num)
           and not in_col(board, col, num)
           and not in_square(board, 
                             row - row % 3, 
                             col - col % 3,
                             num))  

''' Check whether a num is already used in a row '''
def in_row(board, row, num):
    for i in range(SIZE):
        if board[row][i] == num:
            return True
    return False

''' Check whether a num is already used in a col '''
def in_col(board, col, num):
    for i in range(SIZE):
        if board[i][col] == num:
            return True
    return False

''' Check whether a num is already used in a square '''
def in_square(board, row, col, num):
    for i in range(int(math.sqrt(SIZE))):
        for j in range(int(math.sqrt(SIZE))):
            if board[i + row][j + col] == num:
                return True
    return False

'''
    Functions Used to Solve Board
'''
''' Check if the board has any unfilled slots'''
def empty_location(board):
    for i in range(SIZE):
        for j in range(SIZE):
            if board[i][j] == 0:
                return (i,j)
    return False

''' Backtracing Solve Method '''
def solve(board):
    coord = empty_location(board)
    if not coord:
        return True

    for num in range(1,SIZE + 1):
        if check_safe(board, coord[0], coord[1], num):
            board[coord[0]][coord[1]] = num
            if solve(board):
                return True
            board[coord[0]][coord[1]] = 0
    return False

''' Main Method '''
def main():   
    filename = sys.argv[1]
    board = load_file(filename)

    if solve(board):        
        pprint.pprint(board)
    else:
        print("Impossible to solve")


if __name__ == "__main__":
    main()
