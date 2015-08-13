package TreeLibrary;

class LogUtil{
	public static void Begin(){
		String fullClassName = Thread.currentThread().getStackTrace()[3].getClassName();
		String methodName = Thread.currentThread().getStackTrace()[3].getMethodName();
		int lineNumber = Thread.currentThread().getStackTrace()[3].getLineNumber();

		
		System.out.printf(fullClassName +"." +  methodName +"(" + lineNumber + ") >>> BEGIN \n");
	}
	public static void End(){
		String fullClassName = Thread.currentThread().getStackTrace()[3].getClassName();
		String methodName = Thread.currentThread().getStackTrace()[3].getMethodName();
		int lineNumber = Thread.currentThread().getStackTrace()[3].getLineNumber();

		
		System.out.printf(fullClassName +"." +  methodName +"(" + lineNumber + ") <<<< END \n");
	}
	
	
	public static void Log(String format, String... msg){
		String fullClassName = Thread.currentThread().getStackTrace()[3].getClassName();
		String methodName = Thread.currentThread().getStackTrace()[3].getMethodName();
		int lineNumber = Thread.currentThread().getStackTrace()[3].getLineNumber();
		
		String strLog = fullClassName +"." +  methodName +"(" + lineNumber + ")>>>";
		String strVar = String.format(format, msg);
		System.out.printf( strLog  +strVar + "\n");
	}
}