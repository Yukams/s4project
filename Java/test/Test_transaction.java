package test;

import main.TransactionUnit;
import main.Transactions;

public class Test_transaction {

	public static void main(String[] args) {
		System.out.println("Transaction 1 :");
		
		Transactions tList = new Transactions();
		tList.addTransaction("Pierre", "Paul", 2);
		TransactionUnit t1 = tList.getTrans_list()[0];
		
		String check_source = t1.getSource();
		if(check_source == "Pierre") {
			System.out.println("	[OK] * source : " + check_source);
		} else {
			System.out.println("	[KO] * source : " + check_source + " /// should be 'Pierre'");
		}
		
		String check_destination = t1.getDestination();
		if(check_destination == "Paul") {
			System.out.println("	[OK] * destination : " + check_destination);
		} else {
			System.out.println("	[KO] * destination : " + check_destination + " /// should be 'Paul'");
		}
		
		int check_randint = t1.getRandint();
		System.out.println("	     * randint : " + check_randint);
		
		double check_value = t1.getValue();
		if(check_value == 2) {
			System.out.println("	[OK] * value : " + check_value);
		} else {
			System.out.println("	[KO] * value : " + check_value + " /// should be '2'");
		}
		
		double check_value_toSatoBnb = t1.toSatoBnb(check_value);
		if(check_value_toSatoBnb == 200000000) {
			System.out.println("	[OK] * value sato bnb : " + check_value_toSatoBnb);
		} else {
			System.out.println("	[KO] * value sato bnb : " + check_value_toSatoBnb + " /// should be '200000000'");
		}
		
		String check_string = t1.getString();
		System.out.println("	     * string : " + check_string);
		
		
		System.out.println("\n\nTransaction 2 :");
		
		tList.addTransaction("Paul", "Pierre", 1);
		
		TransactionUnit t2 = tList.getTrans_list()[1];
		
		String check_source_2 = t2.getSource();
		if(check_source_2 == "Paul") {
			System.out.println("	[OK] * source : " + check_source_2);
		} else {
			System.out.println("	[KO] * source : " + check_source_2 + " /// should be 'Paul'");
		}
		
		String check_destination_2 = t2.getDestination();
		if(check_destination_2 == "Pierre") {
			System.out.println("	[OK] * destination : " + check_destination_2);
		} else {
			System.out.println("	[KO] * destination : " + check_destination_2 + " /// should be 'Pierre'");
		}
		
		int check_randint_2 = t2.getRandint();
		System.out.println("	     * randint : " + check_randint_2);
		
		double check_value_2 = t2.getValue();
		if(check_value_2 == 1) {
			System.out.println("	[OK] * value : " + check_value_2);
		} else {
			System.out.println("	[KO] * value : " + check_value_2 + " /// should be '1'");
		}
		
		double check_value_toSatoBnb_2 = t2.toSatoBnb(check_value_2);
		if(check_value_toSatoBnb_2 == 100000000) {
			System.out.println("	[OK] * value sato bnb : " + check_value_toSatoBnb_2);
		} else {
			System.out.println("	[KO] * value sato bnb : " + check_value_toSatoBnb_2 + " /// should be '100000000'");
		}
		
		String check_string_2 = t2.getString();
		System.out.println("	     * string : " + check_string_2);
	}

}
