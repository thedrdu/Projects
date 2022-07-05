import java.util.*;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class App {

    //Find the index of a stop with a given name in a given list of stops.
    //Returns -1 if not found.
    public static int findStop(ArrayList<Stop> stopList, String name){
        for (int i = 0; i < stopList.size(); i++) {
            if (stopList.get(i).getName().equals(name)) {
                return i;
            }
        }
        return -1;
    }

    public static Stop matchStop(ArrayList<Stop> stopList, String name) {
        int targetIndex = findStop(stopList, name);
        return stopList.get(targetIndex);
    }

    public static void printStopList(ArrayList<Stop> stopList) {
        for (Stop s : stopList) {
            System.out.print("Stop " + s.getName() + " connects with ");
            if (s.getNextStops().size() == 0) {
                System.out.print("nothing");
            } 
            else {
                for (Stop con : s.getNextStops()) {
                    System.out.print(con.getName() + " ");
                }
            }
            System.out.println();
        }
    }

    public static void main(String[] args) throws Exception {
        ArrayList<Stop> stopList = new ArrayList<Stop>();

        BufferedReader br = new BufferedReader(new FileReader("adjlist.in"));
        try {
            String line = br.readLine();
            int stopCount = Integer.parseInt(line);
            for(int i = 0; i < stopCount; i++){
                line = br.readLine();
                stopList.add(new Stop(line));
            }
            line = br.readLine();
            int connectionCount = Integer.parseInt(line);
            for(int i = 0; i < connectionCount; i++){
                line = br.readLine();
                String[] splitted = line.split(" "); //splitted[0] is our stop, everything after is a connection we will add
                int stopIndex = findStop(stopList, splitted[0]);
                for (String s : Arrays.copyOfRange(splitted, 1, splitted.length)) {
                    stopList.get(stopIndex).addConnection(matchStop(stopList, s));
                }
            }
        } finally {
            br.close();
        }

        printStopList(stopList);
    }
}
