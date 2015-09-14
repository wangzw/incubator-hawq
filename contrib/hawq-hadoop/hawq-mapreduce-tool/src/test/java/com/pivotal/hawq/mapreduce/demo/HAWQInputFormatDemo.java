package com.pivotal.hawq.mapreduce.demo;

import com.pivotal.hawq.mapreduce.HAWQInputFormat;
import org.apache.hadoop.conf.Configured;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.Tool;
import org.apache.hadoop.util.ToolRunner;

/**
 * A demo of how to use {@link com.pivotal.hawq.mapreduce.HAWQInputFormat}
 * to output all rows in a HAWQ's table.
 * <p>
 * This demo uses {@code HAWQInputFormat.setInput(conf, db_url, username, password, tableName)}
 * to set table's metadata.
 */
public class HAWQInputFormatDemo extends Configured implements Tool {

	private static void printUsage() {
		System.out.println("HAWQInputFormatDemo <db_url> <table_name> <output_path> [username] [password]");
		ToolRunner.printGenericCommandUsage(System.out);
	}

	@Override
	public int run(String[] args) throws Exception {
		if (args.length < 3) {
			printUsage();
		}

		String dbURL = args[0];
		String tableName = args[1];
		String outputPath = args[2];
		String username = (args.length >= 4) ? args[3] : null;
		String password = (args.length >= 5) ? args[4] : null;

		Job job = new Job(getConf(), "HAWQInputFormatDemo");
		job.setJarByClass(HAWQInputFormatDemo.class);

		job.setInputFormatClass(HAWQInputFormat.class);

		HAWQInputFormat.setInput(job.getConfiguration(), dbURL, username, password, tableName);
		FileOutputFormat.setOutputPath(job, new Path(outputPath));

		job.setMapperClass(HAWQEchoMapper.class);
		job.setNumReduceTasks(0);

		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(Text.class);

		long startTime = System.currentTimeMillis();
		int returnCode = job.waitForCompletion(true) ? 0 : 1;
		long endTime = System.currentTimeMillis();

		System.out.println("Time elapsed: " + (endTime - startTime) + " milliseconds");

		return returnCode;
	}

	public static void main(String[] args) throws Exception {
		int exitCode = ToolRunner.run(new HAWQInputFormatDemo(), args);
		System.exit(exitCode);
	}
}
