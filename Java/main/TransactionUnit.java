package main;

import java.util.Random;

public class TransactionUnit {
	private String source;
	private String destination;
	private int randint;
	private double value;
	private String string;
	
	
	protected TransactionUnit(String source, String destination, double value) {
		 this.source = source;
		 this.destination = destination;
		 this.randint = getRandomNumberInRange(0, 100);
		 this.value = value;
		 this.string = "Source user" + this.source + "-Destination : user" + this.destination + this.randint + this.value;
	}
	
	
	private static int getRandomNumberInRange(int min, int max) {
        if (min >= max) {
            throw new IllegalArgumentException("max must be greater than min");
        }

        Random r = new Random();
        return r.nextInt((max - min) + 1) + min;
    }
	
	public double toSatoBnb(double value) {
	    double new_value = value * Math.pow(10,8);
	    return new_value;
	}

	public double fromSatoBnb(double value) {
	    double new_value = value * Math.pow(10,-8);
	    return new_value;
	}


	/**
	 * @return the source
	 */
	public String getSource() {
		return source;
	}


	/**
	 * @return the destination
	 */
	public String getDestination() {
		return destination;
	}


	/**
	 * @return the randint
	 */
	public int getRandint() {
		return randint;
	}


	/**
	 * @return the value
	 */
	public double getValue() {
		return value;
	}


	/**
	 * @return the string
	 */
	public String getString() {
		return string;
	}
}
