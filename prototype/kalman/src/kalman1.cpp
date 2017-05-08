#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "matrix.h"
#include <unistd.h>

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>

//#define vel 0.3
#define dt .01
#define x_coordinate 0
#define y_coordinate 0
#define PI 3.141592654
#define theta PI/4


float vel=0.3;
float **F_mat, **H_mat , **P_mat , **R_mat , **Q_mat  , **X_mat , **S_mat, **Z_mat , **K_mat;
matrix F(4,4) , H(4,4) , P(4,4) , R(4,4) , Q(4,4) , X(4,1) , S(4,4) , Z(4,4) , K(4,4); 

float** initialize(int row, int col)
{
	float **a ;
	a=(float**)malloc(row*sizeof(float*));

	for(int i=0 ; i < row ; i++)
    	a[i]=(float*)malloc(col*sizeof(float));

	for(int i=0 ; i < row ; i++)
    {
    	for(int j=0;j < col ; j++)
			a[i][j]=0;
    }
    
   return a;
} 


void declare()
{
	std::cout << "check0\n";
	F_mat = initialize(4,4);
	H_mat = initialize(4,4);
	P_mat = initialize(4,4);
	Q_mat = initialize(4,4);
	X_mat = initialize(4,1);
	S_mat = initialize(4,4);
	R_mat = initialize(4,4);
	Z_mat = initialize(4,4);
	K_mat = initialize(4,4);


	F_mat[0][0] = 1;
	F_mat[0][2] = dt;
	F_mat[1][1] = 1;
	F_mat[1][3] = dt;
	F_mat[2][2] = 1;
	F_mat[3][3] = 1;

	H_mat[0][0] = 1;
	H_mat[1][1] = 1;

	P_mat[0][0] = 500;
	P_mat[1][1] = 500;
	P_mat[2][2] = .3;
	P_mat[3][3] = .3;


	Q_mat[2][2] = .0019739698;
	Q_mat[3][3] = .0324408797;

	X_mat[0][0] = x_coordinate;
	X_mat[1][0] = y_coordinate;
	X_mat[2][0] = vel*cos(theta);
	X_mat[3][0] = vel*sin(theta);

	R_mat[0][0] = .3;
	R_mat[1][1] = .3;

	

	F = F.con_to_mtrx(F_mat , 4 ,4);
	H = H.con_to_mtrx(H_mat , 4, 4);
	P = P.con_to_mtrx(P_mat , 4 ,4);
	R = R.con_to_mtrx(R_mat ,4,4);
	Q = Q.con_to_mtrx(Q_mat ,4 ,4);
	X = X.con_to_mtrx(X_mat , 4,1);
	S = S.con_to_mtrx(S_mat , 4 ,4);
	Z = Z.con_to_mtrx(Z_mat , 4 ,4);
	K = K.con_to_mtrx(K_mat ,4 ,4);
}

int main(int argc, char** argv)
{
	float flag = 0;

	
	declare();

	

	ros::init(argc , argv , "kalman1");
	ros::NodeHandle n;
	ros::Publisher chatter_pub = n.advertise<nav_msgs::Odometry>("/robot5/odom", 10);
	ros::Rate loop_rate(50);	

	

	printf("%c\n", 'x');

	float flag1 = 5;

	while(ros::ok())
	{
		

		nav_msgs::Odometry msg1;
		
		msg1.pose.pose.position.x =  X.mat[0][0];
		
		msg1.pose.pose.position.y = X.mat[1][0];
  		//msg->pose.pose.position.z = X.mat[2][0];
	 	/*p.quat_w = msg->pose.pose.orientation.w;
	    p.quat_x = msg->pose.pose.orientation.x;
	    p.quat_y = msg->pose.pose.orientation.y;
	    p.quat_z = msg->pose.pose.orientation.z;*/
	    msg1.twist.twist.linear.x = X.mat[2][0];
	    msg1.twist.twist.linear.y = X.mat[3][0];
	    msg1.twist.twist.linear.z = 0;
	    msg1.twist.twist.angular.x = 0;
	    msg1.twist.twist.angular.y = 0;
	    msg1.twist.twist.angular.z = 0;  

	    int k = 0;
	    for (int i = 0; i < 4; i++)
	    {
	    	for (int j = 0; j < 4; ++j)
	    	{
	    		msg1.pose.covariance[k] = P.mat[i][j];	
	    		k++;
	    	}
    	}	

	    chatter_pub.publish(msg1);
	    


	

		std::cout << "New X" << "\n";
      	X.show();
      	std::cout << "New P" << "\n";
      	P.show();

     	if ((int)flag%20 == 0 && (flag > 1)) 
     	{
     		std::cout << "Reversal 180 degree\n";
     		X.mat[2][0] = -X.mat[2][0];
     		X.mat[3][0] = -X.mat[3][0];

     		flag+=2;
     	}
   
      	else if( abs(flag - flag1) < .1)
      	{

	        std::cout << "NOISE NOISE NOISE NOISE!!!!!";

	       	P=(F*P)*F.transpose() + Q;
	        X=F*X;
	       
	        flag1 += 5;
        	flag+=0.85;

    	}
    	
    	else
  		{

        	P=(F*P)*F.transpose();
    		X=F*X;
		}


		/*Z = H*X + W;
    
     	S = H*(P*H.transpose()) + R;
     
     	K = P*H.transpose()*S.inv();
     	X = X + K*(Z - H*X);
     	P = (I - K*H)*P;*/
		
		
		printf("%s %f\n", "Flag" , flag );
		flag += dt;
		ros::spinOnce();
	    loop_rate.sleep();
	   
	
	}


	std::cout << X_mat[3][0];
	return 0;
}