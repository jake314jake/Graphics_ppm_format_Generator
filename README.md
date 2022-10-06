# Graphics_ppm_format_Generator
### what Graphics_ppm_format_Generator project for?
> generate a basic 2D graphics shapes (lines ,triangles..) in a ppm file format
### Requirements&Tools 🔧 
  1.GIMP (for the resault) // in tools file
  
  2.File viewer plus 4 (for the ppm file format ) // in tools file
  
  3.a c++ IDE 
### what is ppm format?

a file contain metadata(type ,width,height) + pixel values(RGB for ex)

![rgb](https://user-images.githubusercontent.com/90989827/194344502-4c2a5ce4-0f10-4d52-96cf-4ad42b2c6416.png)

#### .ppm format for this picture is:
P3           // "P3" means this is a RGB color image in ASCII

3 2          // "3 2" is the width and height of the image in pixels

255         // "255" is the maximum value for each color

// The part above is the header

// The part below is the image data: RGB triplets

255   0   0  // red

  0 255   0  //green
  
  0   0 255  // blue
  
255 255   0  // yellow

255 255 255  // white

  0   0   0  // black
  ##### the project writen in c++ with OPP 
  #### a Demo 
  Draw a line in 10*10 px image from (0,0) to (9,9):
  
  ![test](https://user-images.githubusercontent.com/90989827/194347297-656c86da-ba3c-47ce-a08e-9ed8839e6a9d.png)

(img from GIMP) 
  
### Contributing 💡
If you want to contribute to this project and make it better with new ideas, your pull request is very welcomed.
If you find any issue just put it in the repository issue section, thank you.
