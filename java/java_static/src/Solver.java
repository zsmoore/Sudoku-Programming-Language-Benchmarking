import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

/**
 * Class for solving Sudoku in a static way
 */
public class Solver {

    /**
     * Reads in a 2d grid from file
     * @param filename file to be read from
     * @return 2d grid parsed from file
     */
    private static ArrayList<ArrayList<Integer>> readInFile(String filename) {
        List<String> allLines = null;
        ArrayList<ArrayList<Integer>> grid = null;
        try{
            allLines = Files.readAllLines(Paths.get(filename));
        } catch (IOException e) {
            System.out.println("File does not exist");
            System.exit(0);
        }

        if (allLines != null) {
            grid = new ArrayList<>();
            for (String line : allLines) {
                grid.add(Arrays.stream(line.split(" "))
                        .map(Integer::parseInt)
                        .collect(Collectors.toCollection(ArrayList::new)));
            }

            for (ArrayList nums : grid) {
                if (nums.size() != grid.size()) {
                    System.out.println("Your Grid's dimensions are incorrect");
                    System.exit(0);
                }
            }
        } else {
            System.out.println("There were no lines in your file");
            System.exit(0);
        }
        return grid;
    }

    /**
     * Prints our a 2d Array of Integers
     * @param grid the grid to be printed
     */
    private static void printGrid(ArrayList<ArrayList<Integer>> grid) {
        for (ArrayList<Integer> nums : grid) {
            System.out.print("[");
            for (Integer num : nums) {
                System.out.print(num + " ");
            }
            System.out.print("]\n");
        }
    }

    /**
     * Check a row in the grid for a number
     * @param grid Grid to be checked
     * @param row Row in grid to be checked
     * @param num Number to be checked for
     * @return If the specified number is in the row or not
     */
    private static boolean inRow(ArrayList<ArrayList<Integer>> grid, int row, int num) {
        return grid.get(row).contains(num);
    }

    /**
     * Check a col in the grid for a number
     * @param grid Grid to be checked
     * @param col Col in grid to be checked
     * @param num Number to be checked for
     * @return If the specified number is in the col or not
     */
    private static boolean inCol(ArrayList<ArrayList<Integer>> grid, int col, int num) {
        return grid.stream()
                .map(numList -> numList.get(col))
                .collect(Collectors.toList())
                .contains(num);
    }

    private static boolean inSquare(ArrayList<ArrayList<Integer>> grid, int col, int row, int num) {
        return false;
    }

    public static void main(String[] args) {

        if (args.length < 1) {
            System.out.println("Too Few Args");
            System.exit(0);
        }

        ArrayList<ArrayList<Integer>> grid = readInFile(args[0]);
        printGrid(grid);


    }

}
