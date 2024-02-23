#include <stdio.h>

int main()
{
	int n, in, out, bsize, bucket = 0;
	printf("Enter the Bucket Size: ");
	scanf("%d", &bsize);
	printf("Enter the Packet Outging Rate: ");
	scanf("%d", &out);
	printf("Enter the number of inputs: ");
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		printf("\nEnter the Incoming packet-%d size: ", i + 1);
		scanf("%d", &in);
		if (in <= (bsize - bucket))
		{
			bucket += in;
			printf("Bucket status: %d out of %d\n", bucket, bsize);
		}
		else
		{
			printf("Dropped Packet: %d\n", in-(bsize-bucket));
			printf("Bucket Status: %d out of %d\n", bucket, bsize);
			bucket = bsize;
		}
		bucket -= out;
		printf("After outgoing, Bucket Status: %d out of %d\n", bucket, bsize);
	}

	return 0;
}