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

	//These are manual tests that test the URLs in sections (scheme, authority, port, path, and query)
	public void testManualTest()
	{
		UrlValidator urlVal = new UrlValidator(null, null, 0);

		// Tests we expect to pass

		//Should pass, valid URLs (Valid Scheme, Authority, Port, Path, and Query)
		assertTrue(urlVal.isValid("http://www.google.com:80/test1?action=view"));
		assertTrue(urlVal.isValid("ftp://go.com:65535/test1/?action=edit&mode=up"));
		assertTrue(urlVal.isValid("ftp://255.255.255.255:0/test4?action=view"));
		assertTrue(urlVal.isValid("http://255.com:86/$23?action=edit&mode=up"));
		assertTrue(urlVal.isValid("ftp://go.au:65535/test1/file?action=view"));
		assertTrue(urlVal.isValid("http://0.0.0.0:264/t123?action=view"));

		//Empty Port should pass
		assertTrue(urlVal.isValid("ftp://go.com/test1/?action=edit&mode=up"));
		assertTrue(urlVal.isValid("http://255.com/$23?action=edit&mode=up"));
		assertTrue(urlVal.isValid("ftp://go.au/test1/file?action=view"));

		//Empty Path should pass
		assertTrue(urlVal.isValid("http://www.google.com:80?action=view"));
		assertTrue(urlVal.isValid("ftp://go.com:65535?action=edit&mode=up"));
		assertTrue(urlVal.isValid("http://255.com:86?action=edit&mode=up"));    

		//Empty Query should pass
		assertTrue(urlVal.isValid("http://www.google.com:80/test1"));
		assertTrue(urlVal.isValid("ftp://go.au:65535/test1/file"));
		assertTrue(urlVal.isValid("http://255.com:86/$23"));    

		//Real world URL. Found the missing tilde and forward slash in regex string variable
		assertTrue(urlVal.isValid("http://web.engr.oregonstate.edu/~redfiels/classes/cs271/HammingCodes/"));

		//Tests we expect to fail

		//Should fail for empty Scheme
		assertFalse(urlVal.isValid("www.google.com:80/test1?action=view"));
		assertFalse(urlVal.isValid("255.255.255.255:0/test4?action=view"));
		assertFalse(urlVal.isValid("go.au:65535/test1/file?action=view"));

		//Should fail for empty Authority
		assertFalse(urlVal.isValid("ftp://:65535/test1/file?action=view"));
		assertFalse(urlVal.isValid("h3t://:0/test4?action=view"));
		assertFalse(urlVal.isValid("ftp://:65535/test1/?action=edit&mode=up"));     


		//Should fail for invalid Scheme
		assertFalse(urlVal.isValid("3ht://www.google.com:80/test1?action=view"));
		assertFalse(urlVal.isValid("http:/0.0.0.0:264//t123?action=view"));
		assertFalse(urlVal.isValid("://255.255.255.255:0/test4?action=view"));

		//Should fail for invalid authority
		assertFalse(urlVal.isValid("ftp://256.256.576.2555:65535/test1/?action=view"));
		assertFalse(urlVal.isValid("http://1.2.3.4.5:86/$23?action=edit&mode=up"));
		assertFalse(urlVal.isValid("h3t://go.a1a:0/test4?action=view"));

		//Should fail for invalid port
		assertFalse(urlVal.isValid("h3t://255.255.255.255:-1/test4?action=view"));
		assertFalse(urlVal.isValid("ftp://go.au:65636/test1/file?action=view"));
		assertFalse(urlVal.isValid("h3t://0.0.0.0:65a//t123?action=view"));

		//Should fail for invalid path
		assertFalse(urlVal.isValid("http://www.google.com:80/..?action=view"));
		assertFalse(urlVal.isValid("ftp://go.com:65535/../?action=edit&mode=up"));
		assertFalse(urlVal.isValid("ftp://go.com:65535/..//file?action=edit&mode=up"));

		//Should fail for invalid query
		assertFalse(urlVal.isValid("http://www.google.com:80/test1 @action.go"));
		assertFalse(urlVal.isValid("ftp://go.au:65535/test1/file// ?action/travel"));
		assertFalse(urlVal.isValid("ftp://go.au:65535/test1/file ?edit?view"));
	}

   //This tests the boolean aspect of the ResultPair class
	public void testResultPair()
	{
		//Create a few result pairs to compare    
		ResultPair[] testUrl = {new ResultPair("a", true),new ResultPair("b", true)};       

		boolean expected = true;    

		//& the boolean variables together
		for (int index = 0; index < 1; ++index) {           
			expected &= testUrl[index].valid;
		}

		//All true went in, should come out true
		assertTrue(expected);
	}

	public void testSchmePartition(){
		UrlValidator urlValidator= new UrlValidator(null, null, 0);
		assert urlValidator.isValid("http://google.com") == true: "correct scheme is not passing isValid";
		assert urlValidator.isValid("hp://google.com") == false: "valid scheme is passing isValid";
		assert urlValidator.isValid("hTTp://google.com") == true: "correct scheme is not passing isValid";
		assert urlValidator.isValid("http:/google.com") == false: "valid scheme is passing isValid";
		assert urlValidator.isValid("http:|/google.com") == false: "valid scheme is passing isValid";
	}

	public void testAuthorityPartition(){
		UrlValidator urlValidator= new UrlValidator(null, null, 0);
		assert urlValidator.isValid("google.5h") == false: "valid authority is passing isValid";
		assert urlValidator.isValid("1.23.212.1") == false: "valid authority is passing isValid";
		assert urlValidator.isValid("http://Google.com") == true: "correct authority is not passing isValid";
		assert urlValidator.isValid("http://google.coM") == true: "correct authority is not passing isValid";
		assert urlValidator.isValid("http://0.0.0.0") == true: "correct authority is not passing isValid";
		assert urlValidator.isValid("") == false: "valid authority is passing isValid";
		assert urlValidator.isValid("http://google.com") == true: "correct authority is not passing isValid";
	}

	public void testPortPartition(){
		UrlValidator urlValidator= new UrlValidator(null, null, 0);
		assert urlValidator.isValid("http://google.com:123") == true: "correct port is not passing isValid";
		assert urlValidator.isValid("http://google.com:123GH") == true: "valid port is passing isValid";
		assert urlValidator.isValid("http://google.com:GHFD") == true: "valid port is passing isValid";
	}

	public void testPathPartition(){
		UrlValidator urlValidator= new UrlValidator(null, null, 0);
		assert urlValidator.isValid("http://google.com/file") == true: "correct path is not passing isValid";
		assert urlValidator.isValid("http://google.com/File") == true: "correct path is not passing isValid";
		assert urlValidator.isValid("http://google.com/file123") == true: "correct path is not passing isValid";
		assert urlValidator.isValid("http://google.com/....../file") == false: "valid path is passing isValid";
		assert urlValidator.isValid("http://google.com/....") == false: "valid path is passing isValid";
	}

	public void testQueryPartition(){
		UrlValidator urlValidator= new UrlValidator(null, null, 0);
		assert urlValidator.isValid("http://google.com?action=hide") == true: "correct path is not passing isValid";
	}

	/*********************************************************************
	 * Function: testIsValid
	 * Purpose: testIsValid runs through all possible combinations of
	 *          each test segment and tests it using UrlValidator.isValid.
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
