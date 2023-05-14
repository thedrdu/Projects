import java.util.Scanner;
import java.util.Random;

public class SlotMachine{
    public static void main(String[] args) {
        Scanner inputScanner = new Scanner(System.in);
        Random rand = new Random();
        System.out.println("Welcome to the casino!");
        boolean playing = true;
        int chipCount = 100;

        while(playing){
            if(chipCount == 0){
                System.out.println("\nYou have been kicked out of the casino for having no money!");
                break;
            }
            System.out.println("\nPlayer's chips: [$" + chipCount + "]");
            System.out.print("1) Play Slots\n2) Credits\n3) Quit\n\nInput your command: ");
            char inputChar = inputScanner.next().charAt(0);
            switch(inputChar){
                case '1':
                    System.out.print("\nPlease input your bet: $");
                    int bet = inputScanner.nextInt();
                    if(bet > chipCount){
                        System.out.println("Not enough funds!");
                        break;
                    }
                    
                    String roll = generateRoll(rand);
                    int result = getResult(roll, bet);
                    
                    chipCount += result;
                    System.out.println("--------------\nYour roll: " + roll + "\nProfit: $" + result + "\n--------------");
                    break;
                case '2':
                    System.out.println("\n--------------\nCoded with love by thedrdu!\n--------------");
                    break;
                case '3':
                    playing = false;
                    break;
            }
        }
        inputScanner.close();
    }

    public static String generateRoll(Random rand){
        StringBuilder str = new StringBuilder();
        for(int i = 0; i < 3; i++){
            int randomNumber = rand.nextInt(6) + 2;
            str.append(randomNumber);
        }
        return str.toString();
    }

    public static int getResult(String roll, int bet){
        boolean threeOfAKind = roll.charAt(0) == roll.charAt(1) && roll.charAt(1) == roll.charAt(2);
        if(threeOfAKind){
            if(roll.charAt(0) == '7'){
                return bet*10;
            }
            else{
                return bet*5;
            }
        }
        else if(roll.charAt(0) == roll.charAt(1) || roll.charAt(1) == roll.charAt(2) || roll.charAt(0) == roll.charAt(2)){
            return bet*3;
        }
        return -bet;
    }

}
