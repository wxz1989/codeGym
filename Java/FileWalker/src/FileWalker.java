import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.stream.Stream;

public class FileWalker {

	private static void getAllFiles(File curDir) {

		try (Stream<Path> paths = Files.walk(Paths.get("/Users/rakesh/Documents"))) {
		    paths
		        .filter(Files::isRegularFile)
		        .forEach(System.out::println);
		}
		catch( Exception exe ) {
			exe.printStackTrace();
		}
    }
	
	public static void  main(String args[]) {
		File curDir = new File(".");
	     getAllFiles(curDir);
	     curDir = null;
	} 
}
