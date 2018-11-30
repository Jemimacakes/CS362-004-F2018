

import junit.framework.AssertionFailedError;
import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {

	
	ResultPair[] schemePair =	{
									new ResultPair("http://", true),
									new ResultPair("https://", true),
									new ResultPair("ftp://", true),
									new ResultPair("mailto://", true),
									new ResultPair("file://", true),
									new ResultPair("data://", true),
									new ResultPair("irc://", true),
									new ResultPair("://", false),
									new ResultPair("ht:tp://", false),
									new ResultPair("ht/tps://", false),
									new ResultPair("", false)
								};
	
	ResultPair[] userInfoPair =	{
									new ResultPair("", true),
									new ResultPair("username@", true),
									new ResultPair("username:password@", true),
									new ResultPair("username:password@", true)
								};
	
	ResultPair[] hostPair =		{
									new ResultPair("www.google.com", true),
									new ResultPair("oregonstate.edu", true),
									new ResultPair("google.cn", true),
									new ResultPair("127.0.0.1", true),
									new ResultPair("255.255.255.255", true),
									new ResultPair("www.google.co1m", false),
									new ResultPair("hel.lo", false),
									new ResultPair("256.256.256.256", false),
									new ResultPair("", false)
								};
	
	ResultPair[] portPair =		{
									new ResultPair("", true),
									new ResultPair(":80", true),
									new ResultPair(":1234", true),
									new ResultPair(":65535", true),
									new ResultPair(":-1234", false),
									new ResultPair(":65536", false),
									new ResultPair(":8e", false)
								};
	
	ResultPair[] pathPair =		{
									new ResultPair("", true),
									new ResultPair("/myFile1", true),
									new ResultPair("/myFile1/", true),
									new ResultPair("/myDir1/myFile2", true),
									new ResultPair("//myFile3", false),
									new ResultPair("/myDir2//myFile4", false)
								};
	
	ResultPair[] queryPair =	{
									new ResultPair("", true),
									new ResultPair("?myVar=testVal", true),
									new ResultPair("?myVar1=testVal1&myVar2=testVal2", true),
									new ResultPair("?myVar = testVal", false),
								};
   
   Object[] URLPairs = {schemePair, userInfoPair, hostPair, portPair, pathPair, queryPair};
   
	
   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
	public void testManualTest()
	{
		
	}
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {   
	   int testIter = 1;
	   UrlValidator urlValidator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   for(ResultPair curScheme : (ResultPair[]) URLPairs[0])
	   { 
		   for(ResultPair curUserInfo : (ResultPair[]) URLPairs[1])
		   {
			   for(ResultPair curHost : (ResultPair[]) URLPairs[2])
			   {
				   for(ResultPair curPort : (ResultPair[]) URLPairs[3])
				   {
					   for(ResultPair curPath : (ResultPair[]) URLPairs[4])
					   {
						   for(ResultPair curQuery : (ResultPair[]) URLPairs[5])
						   {
							   String testURL = curScheme.item + curUserInfo.item + curHost.item + curPort.item + curPath.item + curQuery.item;
							   
							   boolean testExpectation;
							   if(curScheme.item.equals("file://") && (curUserInfo.item.contains(":") || curPort.item.contains(":")))
							   {
								   testExpectation = false;
							   }
							    if(curScheme.item.equals("file://"))
							   {
								   testExpectation = curScheme.valid & curPath.valid & curQuery.valid;
							   }
							   else
							   {
								   testExpectation = curScheme.valid & curUserInfo.valid & curHost.valid & curPort.valid & curPath.valid & curQuery.valid;
							   }
							   
							   boolean testResult;
							   try
							   {
								   testResult = urlValidator.isValid(testURL);
								   
								   System.out.printf("Test %d: %s is valid: %b [Expect %b]\n", testIter, testURL, testResult, testExpectation);
								   
								   assertEquals(testURL, testExpectation, testResult);   
							   }
							   catch(AssertionFailedError e)
							   {
								   System.out.printf("Testing %s failed - mismatched expectation and result\n", testURL);
							   }
							   catch(Exception e)
							   {
								   System.out.printf("Testing %s failed - threw an exception from isValid\n", testURL);
							   }
							   catch(Error e)
							   {
								   System.out.printf("Testing %s failed - threw an error from isValid\n", testURL);
							   }
							   
							   testIter++;
						   }
					   }
				   }
			   }
		   }	   
	   }
   }
}
