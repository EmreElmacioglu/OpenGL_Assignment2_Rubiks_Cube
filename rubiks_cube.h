
#include "include/Angel.h"

typedef vec4 point4;
typedef vec4 color4;

const int NumVertices = 36;
point4 points[NumVertices * 4 * 8];

//An array that stores which square is on which face
int faces[6][4] = {
  {0, 1, 3, 2},
  {1, 5, 7, 3},
  {5, 4, 6, 7},
  {4, 0, 2, 6},
  {4, 5, 1, 0},
  {2, 3, 7, 6}
};

//An array that stores subcubes neighbouring to a face 
int cube_neighbours[6][4] = {
  {4, 1, 5, 3},
  {4, 2, 5, 0},
  {4, 3, 5, 1},
  {4, 0, 5, 2},
  {2, 1, 0, 3},
  {0, 1, 2, 3}
};

struct rubiks_cube {

  // Vertices of two triangles
  point4 cube_vertices[8] = {
    point4( -0.5, -0.5,  0.5, 1.0 ),
    point4( -0.5,  0.5,  0.5, 1.0 ),
    point4(  0.5,  0.5,  0.5, 1.0 ),
    point4(  0.5, -0.5,  0.5, 1.0 ),
    point4( -0.5, -0.5, -0.5, 1.0 ),
    point4( -0.5,  0.5, -0.5, 1.0 ),
    point4(  0.5,  0.5, -0.5, 1.0 ),
    point4(  0.5, -0.5, -0.5, 1.0 )
  };

  color4 cube_colors[8] = {
    color4(0.0, 0.0, 0.0, 1.0), //Black
    color4(1.0, 0.0, 0.0, 1.0), //Red
    color4(0.0, 1.0, 0.0, 1.0), //Green
    color4(0.0, 0.0, 1.0, 1.0), //Blue
    color4(1.0, 0.584, 0.0, 1.0), //Orange
    color4(1.0, 1.0, 0.0, 1.0), //Yellow
    color4(1.0, 1.0, 1.0, 1.0) //White
  };

  int Index = 0;
  void
  quad( int a, int b, int c, int d )
  {
    points[Index] = cube_vertices[a]; Index++;
    points[Index] = cube_vertices[b]; Index++;
    points[Index] = cube_vertices[c]; Index++;
    points[Index] = cube_vertices[a]; Index++;
    points[Index] = cube_vertices[c]; Index++;
    points[Index] = cube_vertices[d]; Index++;
  }

  void generate() {
    quad( 1, 0, 3, 2 );
    quad( 2, 3, 7, 6 );
    quad( 3, 0, 4, 7 );
    quad( 6, 5, 1, 2 );
    quad( 4, 5, 6, 7 );
    quad( 5, 4, 0, 1 );
  }

  int mod(int a, int b) {
    return ((a % b) + b) % b;
  }

  void create_rubiks_cube(point4 (&subcubes)[8][36 * 4], point4 (&rot_arr)[8][36 * 4], color4 (&colors)[8][36 * 4], point4 (&base)[8][36 * 4]) {

    generate();

    for(int i = 0; i < 36; i++) {

      point4 temp = points[i];
      vec4 translation;
      int index = 0;

      //Upper-left-front cube
      translation = vec4(-0.5, 0.5, 0.5, 0.0);
      subcubes[0][index + i] = temp + translation;
      colors[0][index + i] = cube_colors[0];
      index += 36;

      //Side 1
      subcubes[0][index + i] = Scale(0.90) * temp + vec4(0.0, 0.0, 0.08, 0.0) + translation;
      colors[0][index + i] = cube_colors[1];
      index += 36;
      //Side 2
      subcubes[0][index + i] = Scale(0.90) * temp + vec4(-0.08, 0.0, 0.0, 0.0) + translation;
      colors[0][index + i] = cube_colors[2];
      index += 36;
      //Side 3
      subcubes[0][index + i] = Scale(0.90) * temp + vec4(0.0, 0.08, 0.0, 0.0) + translation;
      colors[0][index + i] = cube_colors[6];

      index = 0;
      //Upper-right-front-cube
      translation = vec4(0.5, 0.5, 0.5, 0.0);
      subcubes[1][index + i] = temp + translation;
      colors[1][index + i] = cube_colors[0];
      index += 36;

      subcubes[1][index + i] = Scale(0.90) * temp + vec4(0.0, 0.0, 0.08, 0.0) + translation;
      colors[1][index + i] = cube_colors[1];
      index += 36;
      subcubes[1][index + i] = Scale(0.90) * temp + vec4(0.08, 0.0, 0.0, 0.0) + translation;
      colors[1][index + i] = cube_colors[5];
      index += 36;
      subcubes[1][index + i] = Scale(0.90) * temp + vec4(0.0, 0.08, 0.0, 0.0) + translation;
      colors[1][index + i] = cube_colors[6];

      index = 0;
      //Lower-left-front cube
      translation = vec4(-0.5, -0.5, 0.5, 0.0);
      subcubes[2][index + i] = temp + translation;
      colors[2][index + i] = cube_colors[0];
      index += 36;

      subcubes[2][index + i] = Scale(0.90) * temp + vec4(0.0, 0.0, 0.08, 0.0) + translation;
      colors[2][index + i] = cube_colors[1];
      index += 36; 
      subcubes[2][index + i] = Scale(0.90) * temp + vec4(-0.08, 0.0, 0.0, 0.0) + translation;
      colors[2][index + i] = cube_colors[2];
      index += 36; 
      subcubes[2][index + i] = Scale(0.90) * temp + vec4(0.0, -0.08, 0.0, 0.0) + translation;
      colors[2][index + i] = cube_colors[3];

      index = 0;
      //Lower-right-front-cube
      translation = vec4(0.5, -0.5, 0.5, 0.0);
      subcubes[3][index + i] = temp + translation;
      colors[3][index + i] = cube_colors[0];
      index += 36;

      subcubes[3][index + i] = Scale(0.90) * temp + vec4(0.0, 0.0, 0.08, 0.0) + translation;
      colors[3][index + i] = cube_colors[1];
      index += 36; 
      subcubes[3][index + i] = Scale(0.90) * temp + vec4(0.08, 0.0, 0.0, 0.0) + translation;
      colors[3][index + i] = cube_colors[5];
      index += 36; 
      subcubes[3][index + i] = Scale(0.90) * temp + vec4(0.0, -0.08, 0.0, 0.0) + translation;
      colors[3][index + i] = cube_colors[3];

      index = 0;
      //Upper-left-behind-cube
      translation = vec4(-0.5, 0.5, -0.5, 0.0);
      subcubes[4][index + i] = temp + translation;
      colors[4][index + i] = cube_colors[0];
      index += 36;

      subcubes[4][index + i] = Scale(0.90) * temp + vec4(0.0, 0.0, -0.08, 0.0) + translation;
      colors[4][index + i] = cube_colors[4];
      index += 36; 
      subcubes[4][index + i] = Scale(0.90) * temp + vec4(-0.08, 0.0, 0.0, 0.0) + translation;
      colors[4][index + i] = cube_colors[2];
      index += 36; 
      subcubes[4][index + i] = Scale(0.90) * temp + vec4(0.0, 0.08, 0.0, 0.0) + translation;
      colors[4][index + i] = cube_colors[6];

      index = 0;
      //Upper-right-behind-cube
      translation = vec4(0.5, 0.5, -0.5, 0.0);
      subcubes[5][index + i] = temp + translation;
      colors[5][index + i] = cube_colors[0];
      index += 36;

      subcubes[5][index + i] = Scale(0.90) * temp + vec4(0.0, 0.0, -0.08, 0.0) + translation;
      colors[5][index + i] = cube_colors[4];
      index += 36;
      subcubes[5][index + i] = Scale(0.90) * temp + vec4(0.08, 0.0, 0.0, 0.0) + translation;
      colors[5][index + i] = cube_colors[5];
      index += 36;
      subcubes[5][index + i] = Scale(0.90) * temp + vec4(0.0, 0.08, 0.0, 0.0) + translation;
      colors[5][index + i] = cube_colors[6];

      index = 0;
      //Lower-left-behind-cube
      translation = vec4(-0.5, -0.5, -0.5, 0.0);
      subcubes[6][index + i] = temp + translation;
      colors[6][index + i] = cube_colors[0];
      index += 36;

      subcubes[6][index + i] = Scale(0.90) * temp + vec4(0.0, 0.0, -0.08, 0.0) + translation;
      colors[6][index + i] = cube_colors[4];
      index += 36; 
      subcubes[6][index + i] = Scale(0.90) * temp + vec4(-0.08, 0.0, 0.0, 0.0) + translation;
      colors[6][index + i] = cube_colors[2];
      index += 36; 
      subcubes[6][index + i] = Scale(0.90) * temp + vec4(0.0, -0.08, 0.0, 0.0) + translation;
      colors[6][index + i] = cube_colors[3];

      index = 0;
      //Lower-right-behind-cube
      translation = vec4(0.5, -0.5, -0.5, 0.0);
      subcubes[7][index + i] = temp + translation;
      colors[7][index + i] = cube_colors[0];
      index += 36;

      subcubes[7][index + i] = Scale(0.90) * temp + vec4(0.0, 0.0, -0.08, 0.0) + translation;
      colors[7][index + i] = cube_colors[4];
      index += 36; 
      subcubes[7][index + i] = Scale(0.90) * temp + vec4(0.08, 0.0, 0.0, 0.0) + translation;
      colors[7][index + i] = cube_colors[5];
      index += 36; 
      subcubes[7][index + i] = Scale(0.90) * temp + vec4(0.0, -0.08, 0.0, 0.0) + translation;
      colors[7][index + i] = cube_colors[3];

      for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 36 * 4; j++) {
          rot_arr[i][j] = subcubes[i][j];
          base[i][j] = subcubes[i][j];
        }
      }
    }
  }

  //Returns rotation angle and direction according to the face index
  mat4 getRotation(int face, float angle) {
    mat4 result;
    switch(face) {
    case 0:
      result = RotateZ(-angle);
      break;
    case 1:
      result = RotateX(-angle);
      break;
    case 2:
      result = RotateZ(angle);
      break;
    case 3:
      result = RotateX(angle);
      break;
    case 4:
      result = RotateY(-angle);
      break;
    case 5:
      result = RotateY(angle);
      break;
    }
    return result;
  }

  //Modifies the vertex array when a side rotation occurs
  void modifyRotationArray(point4 (&subcubes)[8][36 * 4], point4 (&rot_arr)[8][36 * 4], int rotation_face, float angle) {
    int face = rotation_face - 1;

    //White spaces and black parts of the cube
    if(face == 6 || face == 7) {
      return;
    }

    for(int i = 0; i < 4; i++){
      for(int j = 0; j < 36 * 4; j++) {
        int index = faces[face][i];
        rot_arr[index][j] = getRotation(face, angle) * subcubes[index][j];
      }
    }
  }

  //Modifies the array that holds which face is in which side according to the rotation 
  void modify_face_array_helper(int face) {

    int temp_arr[6][4];
    std::copy(&faces[0][0], &faces[0][0]+6*4, &temp_arr[0][0]);

    //Rotated face
    for(int i = 0; i < 4; i++) {
      faces[face][(i+1) % 4] = temp_arr[face][i];
    }

    if(face == 0 || face == 1 || face == 2 || face == 3) {
      //Top-to-Right
      faces[cube_neighbours[face][1]][3] = temp_arr[cube_neighbours[face][0]][mod(3-face-1, 4)];
      faces[cube_neighbours[face][1]][0] = temp_arr[cube_neighbours[face][0]][3-face];

      //Right-to-Bottom
      faces[cube_neighbours[face][2]][face] = temp_arr[cube_neighbours[face][1]][3];
      faces[cube_neighbours[face][2]][mod(face+1, 4)] = temp_arr[cube_neighbours[face][1]][0];

      //Bottom-to-Left
      faces[cube_neighbours[face][3]][1] = temp_arr[cube_neighbours[face][2]][face];
      faces[cube_neighbours[face][3]][2] = temp_arr[cube_neighbours[face][2]][mod(face+1, 4)];

      //Left-to-Top
      faces[cube_neighbours[face][0]][mod(3-face-1, 4)] = temp_arr[cube_neighbours[face][3]][1];
      faces[cube_neighbours[face][0]][3-face] = temp_arr[cube_neighbours[face][3]][2];

    } else if(face == 4 ) {
      //All same indices for top face
      for(int i = 0; i < 4; i++){
        faces[cube_neighbours[face][i]][0] = temp_arr[cube_neighbours[face][mod(i-1, 4)]][0];
        faces[cube_neighbours[face][i]][1] = temp_arr[cube_neighbours[face][mod(i-1, 4)]][1];
      } 
    } else if(face == 5 ) {
      //All same indices for bottom face
      for(int i = 0; i < 4; i++){
        faces[cube_neighbours[face][i]][2] = temp_arr[cube_neighbours[face][mod(i-1, 4)]][2];
        faces[cube_neighbours[face][i]][3] = temp_arr[cube_neighbours[face][mod(i-1, 4)]][3];
      }
    }
  }

  void modify_face_array(int rotation_face, int repeat) {

    int face = rotation_face - 1;

    if(face == 6 || face == 7) {
      return;
    }

    for(int i = 0; i < repeat; i++) {
      modify_face_array_helper(face); 
    }
  }

  //Sets picking colors
  void set_picking_colors(point4 *temp) {
    //Front side squares
    for(int i = 0; i < 4; i++) {
      for(int j = 36; j < 36 * 2; j++) {
        temp[(i * 36 * 4) + j] = color4(0.1, 0.1, 0.1, 1.0);
      }
    }

    //Right side squares
    for(int i = 1; i < 8; i+=2) {
      for(int j = 36 * 2; j < 36 * 3; j++) {
        temp[(i * 36 * 4) + j] = color4(0.2, 0.2, 0.2, 1.0);
      }
    }

    //Back side squares
    for(int i = 4; i < 8; i++) {
      for(int j = 36; j < 36 * 2; j++) {
        temp[(i * 36 * 4) + j] = color4(0.3, 0.3, 0.3, 1.0);
      }
    }

    //Left side squares
    for(int i = 0; i < 7; i+=2) {
      for(int j = 36 * 2; j < 36 * 3; j++) {
        temp[(i * 36 * 4) + j] = color4(0.4, 0.4, 0.4, 1.0);
      }
    }

    //Top side squares
    for(int i = 0; i < 2; i++) {
      for(int j = 36 * 3; j < 36 * 4; j++) {
        temp[(i * 36 * 4) + j] = color4(0.5, 0.5, 0.5, 1.0);
      }
    }

    for(int i = 4; i < 6; i++) {
      for(int j = 36 * 3; j < 36 * 4; j++) {
        temp[(i * 36 * 4) + j] = color4(0.5, 0.5, 0.5, 1.0);
      }
    }

    //Bottom side squares
    for(int i = 2; i < 4; i++) {
      for(int j = 36 * 3; j < 36 * 4; j++) {
        temp[(i * 36 * 4) + j] = color4(0.6, 0.6, 0.6, 1.0);
      }
    }

    for(int i = 6; i < 8; i++) {
      for(int j = 36 * 3; j < 36 * 4; j++) {
        temp[(i * 36 * 4) + j] = color4(0.6, 0.6, 0.6, 1.0);
      }
    }
  }
};
