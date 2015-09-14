package com.pivotal.hawq.mapreduce.util;

import static org.junit.Assert.*;

import org.junit.Test;

import com.pivotal.hawq.mapreduce.HAWQException;

public class HAWQConvertUtilTest
{
	@Test
	public void testBytesToInterval()
	{
		byte[] bytes =
		{ 0x00, (byte) 0xff, 0x2d, (byte) 0xce, 0x2a, 0x4f, (byte) 0xfe,
				(byte) 0xe5, (byte) 0xd4, 0x11, 0x22, 0x59, (byte) 0xa4, 0x4e,
				0x14, (byte) 0x94 };
		HAWQException exception = null;
		try
		{
			HAWQConvertUtil.bytesToInterval(bytes, 1);
		}
		catch (HAWQException e)
		{
			exception = e;
		}
		assertNotNull(exception);
	}

	@Test
	public void testByteToBoolean()
	{
		byte b;
		HAWQException exception = null;
		try
		{
			b = 1;
			assertTrue(HAWQConvertUtil.byteToBoolean(b));
		}
		catch (HAWQException e)
		{
			exception = e;
		}
		assertNull(exception);

		try
		{
			b = 0;
			assertFalse(HAWQConvertUtil.byteToBoolean(b));
		}
		catch (HAWQException e)
		{
			exception = e;
		}
		assertNull(exception);

		try
		{
			b = 2;
			HAWQConvertUtil.byteToBoolean(b);
		}
		catch (HAWQException e)
		{
			exception = e;
		}
		assertNotNull(exception);
	}

	@Test
	public void testBytesToShort()
	{
		byte[] bytes =
		{ 0x00, (byte) 0xff };
		HAWQException exception = null;
		try
		{
			HAWQConvertUtil.bytesToShort(bytes, 0);
		}
		catch (HAWQException e)
		{
			exception = e;
		}
		assertNull(exception);

		try
		{
			HAWQConvertUtil.bytesToShort(bytes, 1);
		}
		catch (HAWQException e)
		{
			exception = e;
		}
		assertNotNull(exception);
	}

	@Test
	public void testBytesToInt()
	{
		byte[] bytes =
		{ 0x00, (byte) 0xff, 0x2d, (byte) 0xce };
		HAWQException exception = null;
		try
		{
			HAWQConvertUtil.bytesToInt(bytes, 0);
		}
		catch (HAWQException e)
		{
			exception = e;
		}
		assertNull(exception);

		try
		{
			HAWQConvertUtil.bytesToInt(bytes, 1);
		}
		catch (HAWQException e)
		{
			exception = e;
		}
		assertNotNull(exception);
	}

	@Test
	public void testBytesToFloat()
	{
		byte[] bytes =
		{ 0x00, (byte) 0xff, 0x2d, (byte) 0xce };
		HAWQException exception = null;
		try
		{
			HAWQConvertUtil.bytesToFloat(bytes, 0);
		}
		catch (HAWQException e)
		{
			exception = e;
		}
		assertNull(exception);

		try
		{
			HAWQConvertUtil.bytesToFloat(bytes, 1);
		}
		catch (HAWQException e)
		{
			exception = e;
		}
		assertNotNull(exception);
	}

	@Test
	public void testBytesToLong()
	{
		byte[] bytes =
		{ 0x00, (byte) 0xff, 0x2d, (byte) 0xce, 0x2a, 0x4f, (byte) 0xfe,
				(byte) 0xe5 };
		HAWQException exception = null;
		try
		{
			HAWQConvertUtil.bytesToLong(bytes, 0);
		}
		catch (HAWQException e)
		{
			exception = e;
		}
		assertNull(exception);

		try
		{
			HAWQConvertUtil.bytesToLong(bytes, 1);
		}
		catch (HAWQException e)
		{
			exception = e;
		}
		assertNotNull(exception);
	}

	@Test
	public void testBytesToDouble()
	{
		byte[] bytes =
		{ 0x00, (byte) 0xff, 0x2d, (byte) 0xce, 0x2a, 0x4f, (byte) 0xfe,
				(byte) 0xe5 };
		HAWQException exception = null;
		try
		{
			HAWQConvertUtil.bytesToDouble(bytes, 0);
		}
		catch (HAWQException e)
		{
			exception = e;
		}
		assertNull(exception);

		try
		{
			HAWQConvertUtil.bytesToDouble(bytes, 1);
		}
		catch (HAWQException e)
		{
			exception = e;
		}
		assertNotNull(exception);
	}

}
