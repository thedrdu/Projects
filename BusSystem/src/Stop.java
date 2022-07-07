// The stop class
import java.util.*;

public class Stop {
    // TODO: these should be private
    public String name;
    public ArrayList<Stop> nextStops;
    
    public Stop() {
        this.name = "UNSET";
        this.nextStops = new ArrayList<Stop>();
    }

    public Stop(String name) {
        this.name = name;
        this.nextStops = new ArrayList<Stop>();
    }

    public String getName() {
        return name;
    }

    public void setName(String n) {
        this.name = n;
    }

    public ArrayList<Stop> getNextStops() {
        return nextStops;
    }

    public void addConnection(Stop stop){
        nextStops.add(stop);
    }
}