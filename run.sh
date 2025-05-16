set -e

echo "🔨 Building Docker image..."
docker build -t cpp-array-class-container .

echo "🚀 Running container..."
docker run --rm cpp-array-class-container
