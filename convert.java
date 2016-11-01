import java.awt.image.BufferedImage;
import java.awt.Color;
import java.util.Scanner;
import java.io.File;
import javax.imageio.*;
import java.io.IOException;
import java.io.FileNotFoundException;

class Convert {
    public static void main(String[] args) {
	if (args.length != 2) {
		System.out.println("Usage: Convert inputFile dimension");
		System.exit(1);
	}
	int dimension = Integer.parseInt(args[1]);
        BufferedImage img = new BufferedImage(dimension, dimension, BufferedImage.TYPE_INT_RGB);
        Scanner pixels = null;
        try {
             pixels = new Scanner(new File(args[0]));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        
        while (pixels.hasNextInt()) {
            int x = pixels.nextInt();
            int y = pixels.nextInt();
            int color = pixels.nextInt();
            img.setRGB(x, y, Color.HSBtoRGB(color / 50.0f, 1.0f, 0.5f));
        }
        
        try {
            File outputfile = new File("saved.png");
            ImageIO.write(img, "png", outputfile);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}


