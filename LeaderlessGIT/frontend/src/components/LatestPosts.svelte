<script>
  import Post from './Post.svelte';

  let posts = [];

  async function fetchLatestPosts() {
    try {
      const postsResponse = await fetch('/api/posts');
      const postsData = await postsResponse.json();

      const postsWithAuthors = await Promise.all(
        postsData.map(async (post) => {
          const authorResponse = await fetch(`/api/users/get/${post.author_id}`);
          const author = await authorResponse.json();

          return {
            id: post.id,
            type: post.type,
            title: post.title,
            author: {
              id: author.id,
              username: author.username,
              avatar_url: author.avatar_url,
            },
            timestamp: post.timestamp,
          };
        })
      );

      posts = postsWithAuthors;
    } catch (error) {
      console.error('Error fetching posts or author data:', error);
      posts = [];
    }
  }

  fetchLatestPosts();
</script>

<h1>Latest Posts:</h1>

  {#each posts as post}
    <Post title={post.title} author={post.author.username} timestamp={post.timestamp} />
  {/each}
