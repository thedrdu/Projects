import java.util.*;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.InputStreamReader;

//Ideas: Add fare, add time, add stops not available at certain hours, find shortest/cheapest/fastest routes.

public class App {
    public static ArrayList<Stop> stopList = new ArrayList<Stop>();

    //Find the index of a stop with a given name in a given list of stops.
    //Returns -1 if not found.
    public static int findStop(String name){
        for (int i = 0; i < stopList.size(); i++) {
            if (stopList.get(i).getName().equals(name)) {
                return i;
            }
        }
        return -1;
    }

    public static Stop matchStop(String name) {
        int targetIndex = findStop(name);
        return stopList.get(targetIndex);
    }

    public static ArrayList<Stop> getNext(String s){
        return matchStop(s).getNextStops();
    }

    public static ArrayList<Stop> DFS(Stop stop, Stop target, ArrayList<Stop> visited){
        if(!visited.contains(stop)){
            visited.add(stop);
            if(stop.getName().equals(target.getName())){
                return visited;
            }
            ArrayList<Stop> nextStops = new ArrayList<>(stop.getNextStops());
            for(Stop next : nextStops){
                DFS(next, target, visited);
            }
        }
        return new ArrayList<Stop>();
    }

    public static ArrayList<Stop> findRoute(String start, String end){
        Stop stop = matchStop(start);
        Stop target = matchStop(end);
        ArrayList<Stop> visited = new ArrayList<Stop>();
        DFS(stop, target, visited);
        return visited;
    }

    public static void printStopList() {
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
                int stopIndex = findStop(splitted[0]);
                for (String s : Arrays.copyOfRange(splitted, 1, splitted.length)) {
                    stopList.get(stopIndex).addConnection(matchStop(s));
                }
            }
        } finally {
            br.close();
        }

        // Tests below

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("Enter a command(print/next/route/exit):");
        String input = reader.readLine();

        while(!input.equals("exit")){
            switch(input){
                case "print":
                    printStopList();
                    break;
                case "next":
                    System.out.print("Type a stop:");
                    String stopinput = reader.readLine();
                    for(Stop s : getNext(stopinput)){
                        System.out.print(s.getName() + " ");
                    }
                    System.out.println();
                    break;
                case "route":
                    System.out.print("Type a starting stop:");
                    String start = reader.readLine();
                    System.out.print("Type an ending stop:");
                    String end = reader.readLine();

                    ArrayList<Stop> route = findRoute(start, end); //Returns empty arraylist if route is not possible
                    String output = "";
                    for(Stop s : route){
                        output += s.getName() + " -> ";
                    }
                    if(output.length() > 0){
                        output = output.substring(0, output.length() - 4);
                    }
                    System.out.println(output);
                    break;
            }
            System.out.print("Enter a command(print/next/route/exit):");
            input = reader.readLine();
        }
        return;

        // printStopList();

        // //Print next stops from A
        // for(Stop s : getNext("A")){
        //     System.out.print(s.getName() + " ");
        // }
        // System.out.println();

        // //Find route from A to F
        // ArrayList<Stop> route = findRoute("A", "F"); //Returns empty arraylist if route is not possible
        // String output = "";
        // for(Stop s : route){
        //     output += s.getName() + " -> ";
        // }
        // if(output.length() > 0){
        //     output = output.substring(0, output.length() - 4);
        // }
        // System.out.println(output);

    }
}
