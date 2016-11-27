package diabeticSemanticNetwork;

import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class DiabeticSemanticNetwork {

	private static boolean terminateSimulation = false;
	private static boolean trace = false;

	public static void main(String[] args) {
		// Initialization
		Backbone.addFact("david", "isa", "diabetics");
		Backbone.addFact("diabetics", "shouldAvoid", "sugar");
		Backbone.addFact("candy", "contains", "sugar");
		Backbone.addFact("snickers", "ako", "candy");

		Scanner scanner = new Scanner(System.in);
		try {
			while (!terminateSimulation) {

				System.out.print(">>: ");
				String input = scanner.nextLine();
				String command = "";
				if (input.equals("help")) {
					helpPrint();
					continue;
				}

				if (input.equals("q")) {
					terminateSimulation = true;
					continue;
				}

				if (!input.startsWith("value")) {
					System.out.println("Invalid command, type help for more details");
					continue;
				} else {
					if (input.startsWith("value")) {
						command = "value";
					}
				}

				List<String> arguments = getCommandParams(input);

				if (command.equals("value")) {
					commandValue(arguments);
				}
			}
		} finally {
			scanner.close();
		}

	}

	private static void commandValue(List<String> arguments) {
		if (checkConstant(arguments)) {
			trace = true;
		} else if (checkVariable(arguments)) {
			trace = false;
		} else {
			System.out.println("Enter either variables or Constants");
			return;
		}

		if (!trace) {
			if(Backbone.validateFact( arguments.get(0),  arguments.get(1),  arguments.get(2))) {
				System.out.println("true");
			} else {
				System.out.println("false");
			}
			
		} else {
			Backbone.validateAllFacts( arguments.get(0),  arguments.get(1),  arguments.get(2));
		}
	}

	private static boolean checkConstant(List<String> arguments) {
		return (Character.isUpperCase(arguments.get(0).charAt(0)) && Character.isUpperCase(arguments.get(1).charAt(0)) && Character
				.isUpperCase(arguments.get(2).charAt(0)));
	}

	private static boolean checkVariable(List<String> arguments) {
		return (Character.isLowerCase(arguments.get(0).charAt(0)) && Character.isLowerCase(arguments.get(1).charAt(0)) && Character
				.isLowerCase(arguments.get(2).charAt(0)));
	}

	private static void helpPrint() {
		System.out.println("1. value(a,b,c) : checks if the statement is true");
		System.out.println("2. value(A,B,C) : returns all facts and inferences");
		System.out.println("3. help : shows available commands");
		System.out.println("4. q or Q: terminates the simulation");
		System.out.println("");
	}

	private static List<String> getCommandParams(String command) {

		String arguments = command.substring(command.indexOf("(") + 1, command.indexOf(")"));
		return Arrays.asList(arguments.trim().split("\\s*,\\s*"));
	}
}
