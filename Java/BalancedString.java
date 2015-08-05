
import java.util.*;
import java.io.*;

class BalacendStringImpl{
	private int mStrLength = -1;
	String mInputString = new String("Empty");
	
	private int mStackCounter;
	Stack<Character>  mBalancer;
	
	private final String openingDelimiters = "{([";
	private final String closingDelimiters = "})]";
	
	public void CleanUp(){
		mInputString = null;
		mBalancer.clear();
		mBalancer = null;
	}
	private void Diagnostics(){
		
		System.out.println("Current Stack Status");
		System.out.println("Size:" + mBalancer.size());
		if ( mBalancer.toString().isEmpty() == false ){
			System.out.println("Content:" + mBalancer.toString());
		}
	}
	public void InitImpl(){
		mStrLength = 0;
		mStackCounter = 0;
		mBalancer = new Stack<Character>();
	}
	public void SetString(String input){
		input.trim();
		if ( input.isEmpty() == true || input.length() == 0 ){
			System.out.println("Invalid parameter, please provide valid input string!!!");
			return;
		}
		
		mInputString= input;
		mStrLength = mInputString.length();
		
		return;
	}
	
	public boolean  IsStringBalanced(String strToCheck){
		boolean result = false;
		
		strToCheck.trim();
		
		if ( strToCheck.isEmpty() == true || strToCheck.length() == 0 ){
			System.out.println("Invalid parameter, please provide valid input string!!!");
			return false;
		}
		
		int iCharCount = 0;
		while (iCharCount != mStrLength ){
			
			char toCheck = mInputString.charAt(iCharCount);
			
			//Can be checked with regex but as of now doing it the hard way..
			//Regex implementataion pending...
			if (toCheck == '{' || toCheck == '(' || toCheck == '['){
				Character toPush = new Character(mInputString.charAt(iCharCount));
				mBalancer.push(toPush);	
			} else if (toCheck == '}' || toCheck == ')' || toCheck == ']'){
				
				Character poped = new Character('\n');
				if ( mBalancer.size() >0 ){
					poped = mBalancer.pop();	
				} else {
					System.out.println("Stack is empty when attempting to POP, returning ");
					return false;
				}
				
				if( (poped =='{' &&  toCheck == '}') ||
					(poped=='(' &&  toCheck == ')') ||
					(poped =='['&&  toCheck == ']') ){
					System.out.println("Okay");
				} else { 
					System.out.println("Incorrect mapping, unbalanced string!!!");
					//return false;
					break;
				}
				
				poped = null;
			}
			iCharCount++;
			
			System.out.println("Curernt CharCount:" + iCharCount);
			Diagnostics();
		}

		if ( mBalancer.size() > 0 ){
			System.out.println("Failed, not a balanced string, returning ");
			result = false;
		} else {
			result = true;
		}
		return result;
	}
};

//interface BalancedSringWrapper{
//	public void SetString(String inputString){
//		
//	}
//}

public class BalancedString {
	public static void main(String args[]){
		BalacendStringImpl impl = new BalacendStringImpl();
		impl.InitImpl();
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String line="Empty";
		try {
			line = br.readLine();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		if ( line.equalsIgnoreCase("quit")){
			System.out.println("Quiting this program, Goodbye!!!");
			try {
				br.close();
				impl.CleanUp();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			br = null;
			impl = null;
			return;
		}
		impl.SetString(line);
		if ( impl.IsStringBalanced(line)){
			System.out.println("Balanced String!");
		} else {
			System.out.println("UnBalanced String!");
		}
	}
};

