Mordechai Goldstein
318530136
השיטות הפרטיות שהוספתי עוזרות לי להפוך את הקוד לקריא יותר בכך שהן מבצעות את בדיקות המערך הריק וה null בנפרד
שיטה נוספת עוזרת לסדר את הקריאה של הפונקציה contains בכך שהיא מפרקת את ביצוע הפעולה לפעולה הבודקת הימצאות איבר בתוך מערך ואז חזרה על הפעולה הזו עבור כל איבר במערך הנבדק.
private static boolean isNull(int[][] arr) 
private static boolean isNull(int[] arr) 

private static boolean isIntArrayEmpty(int[] array) 
private static boolean isIntArrayEmpty(int[][] array) 

private static boolean contains(int[] arr, int value) 
