import junit.framework.AssertionFailedError;
import junit.framework.TestCase;

public class UrlValidatorTest extends TestCase {

	// Scheme segment test values
	ResultPair[] schemePair = {
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

	// User info segment test values
	ResultPair[] userInfoPair = {
		new ResultPair("", true),
		new ResultPair("username@", true),
		new ResultPair("username:password@", true),
		new ResultPair("username:password@", true)
	};

	// Host segment test values
	ResultPair[] hostPair = {
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

	// Port segment test values
	ResultPair[] portPair = {
		new ResultPair("", true),
		new ResultPair(":80", true),
		new ResultPair(":1234", true),
		new ResultPair(":65535", true),
		new ResultPair(":-1234", false),
		new ResultPair(":65536", false),
		new ResultPair(":8e", false)
	};

	// Path segment test values
	ResultPair[] pathPair = {
		new ResultPair("", true),
		new ResultPair("/myFile1", true),
		new ResultPair("/myFile1/", true),
		new ResultPair("/myDir1/myFile2", true),
		new ResultPair("//myFile3", false),
		new ResultPair("/myDir2//myFile4", false)
	};

	// Query segment test values
	ResultPair[] queryPair = {
		new ResultPair("", true),
		new ResultPair("?myVar=testVal", true),
		new ResultPair("?myVar1=testVal1&myVar2=testVal2", true),
		new ResultPair("?myVar = testVal", false),
	};

	// Combined test value object
	Object[] URLPairs = {schemePair, userInfoPair, hostPair, portPair, pathPair, queryPair};

	public UrlValidatorTest(String testName) {
		super(testName);
	}

	public void testManualTest()
	{

	}

	public void testYourFirstPartition()
	{

	}

	public void testYourSecondPartition()
	{   

	}

	/*********************************************************************
	 * Function: testIsValid
	 * Purpose: testIsValid runs through all possible combinations of
	 *			each test segment and tests it using UrlValidator.isValid.
	 *********************************************************************/
	public void testIsValid()
	{
		int testIter = 1; // Test iteration counter
		UrlValidator urlValidator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES); // UrlValidator object

		// Loop through all segment arrays
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
								// Construct the URL under test from all current segments
								String testURL = curScheme.item + curUserInfo.item + curHost.item + curPort.item + curPath.item + curQuery.item;

								// Calculate expectation, handling special cases for "file" scheme
								boolean testExpectation;
								if(curScheme.item.equals("file://") && (curUserInfo.item.contains(":") || curPort.item.contains(":")))
								{
									// If scheme is "file" and ':' is located in valid locations of URL, test should fail.
									testExpectation = false;
								}
								if(curScheme.item.equals("file://"))
								{
									// If scheme is "file" without ':', test is based on all segments besides authority segments
									testExpectation = curScheme.valid & curPath.valid & curQuery.valid;
								}
								else
								{
									// Otherwise, expectation is true of all segments are valid and false otherwise
									testExpectation = curScheme.valid & curUserInfo.valid & curHost.valid & curPort.valid & curPath.valid & curQuery.valid;
								}

								// Run test iteration
								boolean testResult;
								try
								{
									// Test constructed URL
									testResult = urlValidator.isValid(testURL);

									// Print test information
									System.out.printf("Test %d: %s is valid: %b [Expect %b]\n", testIter, testURL, testResult, testExpectation);

									// Assert that test results match expectations
									assertEquals(testURL, testExpectation, testResult);   
								}
								catch(AssertionFailedError e)
								{
									// If assertion does not match, print error
									System.out.printf("Testing %s failed - mismatched expectation and result\n", testURL);
								}
								catch(Exception e)
								{
									// If exception thrown by isValid due to bug, print error
									System.out.printf("Testing %s failed - threw an exception from isValid\n", testURL);
								}
								catch(Error e)
								{
									// If error is thrown by isValid due to bug, print error
									System.out.printf("Testing %s failed - threw an error from isValid\n", testURL);
								}

								// Increment test iterator
								testIter++;
							}
						}
					}
				}
			}
		}
	}
}
