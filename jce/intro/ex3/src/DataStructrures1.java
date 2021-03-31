
public class DataStructrures1 {

	public static void main(String[] args) {
		int b[] = {0, -5, 123, -455, 12093, 9, 3, -66};
		sort(b);
		for (int i = 0; i < b.length; i++)
			System.out.print(b[i] + " ");
	}
	public static void sort(int[] a) {
		sort(a, 0);
		
	}
	private static void sort(int[] a, int limiter) {
		if (a.length-2*limiter < 2)
			return;

		swap(a, findMax(a, limiter), a.length - 1 -limiter);
		swap(a, findMin(a, limiter), limiter);	
		sort(a, limiter + 1);
	}
	public static int findMax(int a[], int limiter) {

		int max = Integer.MIN_VALUE,
				maxI = -1;
		for (int i = limiter; i < a.length - limiter; i++) {
			if (a[i] > max)
			{
				maxI = i;
				max = a[i];
			}		
		}
		return maxI;
	}
	public static int findMin(int a[], int limiter) {
		
		int min = Integer.MAX_VALUE,
				minI = -1;
		for (int i = limiter; i < a.length - limiter; i++) {
			if (a[i] < min)
			{
				minI = i;
				min = a[i];
			}		
		}
		return minI;
	}
	public static void swap(int[] array, int i, int j) {
		int tmp = array[i];
		array[i] = array[j];
		array[j] = tmp;
	}
	
}
