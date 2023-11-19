using System;
using System.Collections.Generic;

class command {

    Car currentCar;
    List<String> commands;

    public struct Mode {
        String current;

        public Mode(String m) { current = m; }

        public void changeMode(String m) { current = m; }
        public String checkMode() { return current; }
    }

    public Mode mode;

    public command() {
        mode = new Mode("");
        commands = new List<String>();
    }

    public void reset() {
        mode.changeMode("");
        commands.Clear();
    }
    public void setCar(Car cIn) { currentCar = cIn; }
    public Car getCurrentCar() { return currentCar; }
    public void addCommand(String cIn) { commands.Add(cIn); }
    public String peekCommand() { return commands[0]; }
    public String takeCommand() {

        if (commands.Count == 0) return "";
        String c = commands[0];
        commands.RemoveAt(0);
        return c;
        
    }
    
}

class Car {

    struct Name {

        String nickname;
        
        int year;
        String make;
        String model;
        String package;
        String description;

        public Name(String nicknameIn, int yIn, String makeIn, String modelIn, String packageIn, String descIn = "") {
            nickname = nicknameIn;
            
            year = yIn;
            make = makeIn;
            model = modelIn;
            package = packageIn;
            description = descIn;
        }

        public String getNickname() { return nickname; }

        public String getOfficialName() {
            return year + " " + make + " " + model + " " + package;
        }

        public String getDesc() { return description; }
    }
    
    Name carName;
    DateTime next_service;
    Int32 mileage;
    Int32 mileage_service;

    public Car() {
        carName = new Name(
            askUser("Nickname? "),
            Int32.Parse(askUser("Year? ")),
            askUser("Make? "),
            askUser("Model? "),
            askUser("Package? "),
            askUser("Description? ")
        );
        next_service = DateTime.Parse(askUser("Next service date? (i.e. 01 Nov 2008) "));
        mileage = Int32.Parse(askUser("Mileage? "));
        mileage_service = mileage + 5000;
    }
    Car(Name newCarName, DateTime dateIn, Int32 milesIn, Int32 mileServIn) {

        carName = newCarName;
        next_service = dateIn;
        mileage = milesIn;
        mileage_service = mileServIn;
    }

    public String askUser(String question) {
        Console.WriteLine(question);
        return Console.ReadLine();
    }

    public String getNickname() {
        return carName.getNickname();
    }

    public String getFullName() {
        return carName.getOfficialName();
    }

    public void displayFull() {
        Console.WriteLine(
            "\"" + carName.getNickname() + "\"" + "\n" +
            carName.getOfficialName() + "\n" + 
            carName.getDesc() + "\n" +
            "Specs -->\n" + 
            "ServiceIntervals -->\n" + 
            "ProjectIdeas -->"
        );
            
    }
}


class Program {
    public static Dictionary<string, Car> garage = new Dictionary<string, Car>();
    public static command commands = new command();
    
    public static void Main (string[] args) {
        Console.WriteLine("IN");
        int d = parseRequest(getNextCommand());
        do {
            
            d = parseRequest(getNextCommand());
        } while (d != -1);
    }

    public static String newRequest() {
        
        String userIn = Console.ReadLine();
        if (userIn.Contains(' ')) {
            foreach (String s in userIn.Split(' ')) {
                commands.addCommand(s);
            }
        } else commands.addCommand(userIn);
        
        return commands.takeCommand();
    }

    public static Car checkForAndSetCurrent(String carName) {
        foreach (String s in garage.Keys) if (carName == s) {
            commands.setCar(garage[s]);
            return commands.getCurrentCar();
        }
        return null;
    }
    
    public static String getNextCommand() {
        String s = commands.takeCommand();
        if (s == "") {
            return newRequest();
        }
        return s;
    }

    public static void logCars() {
        foreach (String car in garage.Keys) {
            Console.WriteLine(car);
        }
    }

    public static int parseRequest(string req) {

        switch (req) { // Search, add, edit
        case ("s" or "S"):
            commands.mode.changeMode(req);
            break;
        case ("a" or "A"):
            commands.mode.changeMode(req);
            Car temp = new Car();
            garage.Add(temp.getNickname(), temp);
            break;
        case ("clear" or "CLEAR"):
            commands.reset();
            break;
        case ("quit" or "QUIT"):
            return -1;
        default:
            if (commands.mode.checkMode() == "s") {
                checkForAndSetCurrent(req).displayFull();
            }
            else if (commands.mode.checkMode() == "a") {
                //adding whatever
            }
            break;
        }    
        
        

        return 1;
    }
}
