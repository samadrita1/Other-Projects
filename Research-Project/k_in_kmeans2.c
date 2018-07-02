#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define n 17000		// no of datapoints
#define k 3			// no of clusters
#define d 3			// no of attributes


int min_dist(double a[n][d], double centroids[k][d], int i)
{
	
	int j, l, select = 0;
	double min_d = 0, temp_min_d;
	for(l=0; l<d; l++)
	{
		min_d += (centroids[0][l]-a[i][l]) * (centroids[0][l]-a[i][l]);
	}
	for(j=1; j<k; j++)
	{
		temp_min_d = 0;
		for(l=0; l<d; l++)
		{
			temp_min_d += (centroids[j][l]-a[i][l]) * (centroids[j][l]-a[i][l]);
		}
		if(temp_min_d < min_d)
		{
			min_d = temp_min_d;
			select = j;
		}
	}
	return select;
}

double avg_intraclass_dist(double a[n][d], int b[n][2], int count[k])
{
	int i, j, kc2[k], l, m;
	double sum[k]={0},avg_d=0;
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			if(b[i][1] == b[j][1] && i != j)
			{
				for(l=0;l<d;l++)
				{
					sum[b[i][1]] += (a[j][l] - a[i][l]) * (a[j][l] - a[i][l]);
				} 
			}
		}
	}
	for(i=0; i<k; i++)
	{
		avg_d += sum[i] / count[i] / (count[i]-1);
	}
	avg_d /= k;
	printf("%f\n", avg_d);
	return avg_d;
}

void k_means(double a[n][d], int b[n][2])
{
	int temp, i, j, l;
	double centroids[k][d];
	/*double **centroids = (double **) malloc(k * sizeof(double *));
	for (i=0; i<k; i++)
	{
		centroids[i] = (double *) malloc(d * sizeof(double));
	}*/
	int r[k];
	int count[k] = {0};
	double sum[k][d];
	// generating random centroids
	for(i=0; i<k; i++)
	{
		r[i]=rand()%n;
		for(j=0;j<i;j++)
		{
			if(r[j]==r[i] && i!=j)
			{
				i--;
				break;
			}
		}
	}

	for(i=0;i<k;i++)
	{
		for(j=0;j<d;j++)
		{
			centroids[i][j] = a[r[i]][j];
		}
	}

	do
	{
		temp = 1;
		for(i=0;i<k;i++)
		{
			count[i]=0;
			for(j=0;j<d;j++)
			{
				sum[i][j] = 0;
			}
		}
		for(i=0;i<n;i++)
		{
			b[i][0] = b[i][1];
		}
		
		printf("\n");

		/*for(i=0;i<k;i++)
		{
			printf("%d\n",count[i]);
		}*/
		for(i=0;i<n;i++)
		{	
			b[i][1] = min_dist(a, centroids, i);
			count[b[i][1]]++;			
		}
		for(i=0;i<k;i++)
		{
			printf("%d \n",count[i]);
		}
		printf("END\n");
		
		for(i=0; i<n; i++)
		{
			if(b[i][0] != b[i][1])
			{
				temp = 0;
			}
			//b[i][0] = b[i][1];
		}
		for(i=0;i<n;i++)
		{
			for(j=0;j<d;j++)
			{
				sum[b[i][1]][j] += a[i][j];
			}
		}
		for(i=0;i<k;i++)
		{
			for(j=0;j<d;j++)
			{
				centroids[i][j]=sum[i][j]/count[i];
			}
		}
	}while(temp!=1);

	double avg_intra = avg_intraclass_dist(a, b, count);
}



int main()
{
	int i,j;
	//int n = 100,d = 2,k = 2;
	double a[n][d];
	int b[n][2];
	
	time_t t;
	//initialize array with random nos.
	srand((unsigned) time(&t));

	for(i=0; i<n/k; i++)
	{	
		printf("%d.\t",(i+1));
		for(j=0; j<d; j++)
		{
			a[i][j] = 1+0.01*(rand()%100);
			printf("%f\t",a[i][j]);
		}
		printf("\n");
		b[i][0] = -1;
	}
	for(i = n/k+1; i<2*(n/k); i++)
	{
		printf("%d.\t",(i+1));
		for(j=0;j<d;j++)
		{
			a[i][j] = 3+0.01*(rand()%100);
			printf("%f\t",a[i][j]);
		}
		printf("\n");
		b[i][0] = -1;
	}
	for(i = 2*(n/k)+1; i<n; i++)
	{
		printf("%d.\t",(i+1));
		for(j=0;j<d;j++)
		{
			a[i][j] = 5+0.01*(rand()%100);
			printf("%f\t",a[i][j]);
		}
		printf("\n");
		b[i][0] = -1;
	}

	k_means(a, b);

	/*for(i=0;i<n;i++)
	{
		for(j=0;j<d;j++)
		{
			printf("%f\t",a[i][j]);
		}
		for(j=0;j<2;j++)
		{
			printf("%d\t",b[i][j]);
		}
		printf("\n");
	}*/

	return 0;
}